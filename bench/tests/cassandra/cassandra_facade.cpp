#include <iostream>

#include <boost/algorithm/string.hpp>
#include <bench/tests/cassandra/cassandra_facade.hpp>

#define NAMESPACE "bench.objects"

using namespace bench::tests::cassandra;

cassandra_facade::cassandra_facade()
    : _cluster(cass_cluster_new()),
      _session(cass_session_new())      
{
}

cassandra_facade::~cassandra_facade()
{
    cass_session_free(_session);
    cass_cluster_free(_cluster);
} 

void
cassandra_facade::connect(const std::string & cluster_uri) {
    cass_cluster_set_contact_points(_cluster, cluster_uri.c_str());
    cass_cluster_set_queue_size_io(_cluster, 10000);
    cass_cluster_set_pending_requests_low_water_mark(_cluster, 5000);
    cass_cluster_set_pending_requests_high_water_mark(_cluster, 10000);
    cass_cluster_set_core_connections_per_host(_cluster, 1);
    cass_cluster_set_max_connections_per_host(_cluster, 2);
    cass_cluster_set_max_requests_per_flush(_cluster, 10000);

    CassFuture * connect_future = cass_session_connect(_session, _cluster);
    
    cass_future_wait(connect_future);
    CassError rc = cass_future_error_code(connect_future);
    if (rc != CASS_OK) 
        throw std::runtime_error("Unable to connect: " + cluster_uri);

    cass_future_free(connect_future);
}

/* static */ std::vector<std::string> cassandra_facade::resolve_topology(const std::string & node_uri) {

    CassCluster * cluster = cass_cluster_new();    
    CassSession * session = cass_session_new();    

    cass_cluster_set_contact_points(cluster, node_uri.c_str());

    // Instead of using the default round-robin load balancing policy,
    // we whitelist only a single host. This is required because below
    // we request the local peer ip *and* the remote peers in two
    // separate queries, which goes completely wrong when round-robin
    // load balancing is used.
    //
    // This strategy is also used by the cqlsh command to ensure it
    // keeps talking to the same host.
    cass_cluster_set_whitelist_filtering(cluster, node_uri.c_str());
    
    CassFuture * connect_future = cass_session_connect(session, cluster);    
    
    cass_future_wait(connect_future);
    CassError rc = cass_future_error_code(connect_future);
    if (rc != CASS_OK) 
        throw std::runtime_error("Unable to connect: " + node_uri);

    std::vector<std::string> peers;

    // First, lets retrieve information about the node we are
    // currently connected to.
    char const * select_query = "SELECT broadcast_address FROM system.local;";
    CassStatement * statement = cass_statement_new(select_query, 0);
    CassFuture * select_future = execute(session, statement);

    const CassResult* result = cass_future_get_result(select_future);
    CassIterator* iterator = cass_iterator_from_result(result);

    while (cass_iterator_next(iterator)) {
        const CassRow * row = cass_iterator_get_row(iterator);
        const CassValue * value = cass_row_get_column_by_name(row, "broadcast_address");

        CassInet inet;
        cass_value_get_inet(value, &inet);

        char output[CASS_INET_STRING_LENGTH];
        cass_inet_string(inet, output);

        peers.push_back(output);
    }

    cass_result_free(result);
    cass_iterator_free(iterator);
    cass_future_free(select_future);
    
    // Now, let's request information about all the peers our current
    // contact point is connected to.
    select_query = "SELECT peer FROM system.peers;";
    statement = cass_statement_new(select_query, 0);
    select_future = execute(session, statement);

    result = cass_future_get_result(select_future);
    iterator = cass_iterator_from_result(result);

    while (cass_iterator_next(iterator)) {
        const CassRow * row = cass_iterator_get_row(iterator);
        const CassValue * value = cass_row_get_column_by_name(row, "peer");

        CassInet inet;
        cass_value_get_inet(value, &inet);

        char output[CASS_INET_STRING_LENGTH];
        cass_inet_string(inet, output);

        peers.push_back(output);
    }

    cass_result_free(result);
    cass_iterator_free(iterator);
    cass_future_free(select_future);
    cass_statement_free(statement);
    cass_future_free(connect_future);

    return peers;    
}

void cassandra_facade::remove(const std::string & alias)
{
    char const * delete_query = "DELETE FROM " NAMESPACE " WHERE id = ?";
    CassStatement * statement = cass_statement_new(delete_query, 1);

    cass_statement_bind_string(statement, 0, alias.c_str());

    cass_future_free(
        execute(_session, statement));
    cass_statement_free(statement);
}

void cassandra_facade::blob_put(const std::string & alias, const std::string & content)
{
    char const * insert_query = "INSERT INTO " NAMESPACE " (id, content) VALUES (?, ?)";    
    CassStatement * statement = cass_statement_new(insert_query, 2);

    cass_statement_bind_string(statement, 0, alias.c_str());
    cass_statement_bind_bytes(statement, 1, reinterpret_cast<const cass_byte_t *>(content.c_str()), content.length());
    
    cass_future_free(
        execute(_session, statement));
    cass_statement_free(statement);
}

void cassandra_facade::blob_update(const std::string & alias, const std::string & content)
{
    char const * update_query = "UPDATE " NAMESPACE " SET content = ? WHERE id = ?";
    CassStatement * statement = cass_statement_new(update_query, 2);
    cass_statement_bind_bytes(statement, 0, reinterpret_cast<const cass_byte_t *>(content.c_str()), content.length());
    cass_statement_bind_string(statement, 1, alias.c_str());

    cass_future_free(
        execute(_session, statement));
    cass_statement_free(statement);
}

std::string cassandra_facade::blob_get(const std::string & alias)
{
    char const * select_query = "SELECT content FROM bench.objects WHERE id = ?";    
    CassStatement * statement = cass_statement_new(select_query, 1);
    cass_statement_bind_string(statement, 0, alias.c_str());

    CassFuture * future = execute(_session, statement);

    const CassResult* result = cass_future_get_result(future);
    CassIterator* iterator = cass_iterator_from_result(result);
    if (!cass_iterator_next(iterator))
        throw std::runtime_error("object not found: " + alias);

    const CassRow * row = cass_iterator_get_row(iterator);
    const CassValue * value = cass_row_get_column_by_name(row, "content");

    const cass_byte_t * content;
    size_t content_length;
    cass_value_get_bytes(value, &content, &content_length);

    cass_result_free(result);
    cass_iterator_free(iterator);
    cass_future_free(future);
    cass_statement_free(statement);

    return std::string(reinterpret_cast<const char*>(content), content_length);
}

/* static */ CassFuture *
cassandra_facade::execute(CassSession * session, CassStatement * statement) {
    CassError rc = CASS_OK;
    CassFuture * future = NULL;
    
    future = cass_session_execute(session, statement);
    cass_future_wait(future);

    rc = cass_future_error_code(future);
    if (rc != CASS_OK)  {
        const char* message;
        size_t message_length;

        cass_future_error_message(future, &message, &message_length);
        throw std::runtime_error(message);
    }

    return future;    
}
