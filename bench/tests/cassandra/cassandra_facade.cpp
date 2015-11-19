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
    CassError rc = CASS_OK;
    CassFuture* connect_future = NULL;
    cass_cluster_set_contact_points(_cluster, cluster_uri.c_str());
    cass_cluster_set_queue_size_io(_cluster, 10000);
    cass_cluster_set_pending_requests_low_water_mark(_cluster, 5000);
    cass_cluster_set_pending_requests_high_water_mark(_cluster, 10000);
    cass_cluster_set_core_connections_per_host(_cluster, 1);
    cass_cluster_set_max_connections_per_host(_cluster, 2);
    cass_cluster_set_max_requests_per_flush(_cluster, 10000);

    connect_future = cass_session_connect(_session, _cluster);
    
    cass_future_wait(connect_future);
    rc = cass_future_error_code(connect_future);
    if (rc != CASS_OK) 
        throw std::runtime_error("Unable to connect: " + cluster_uri);

    cass_future_free(connect_future);
}

/* static */ std::vector<std::string> cassandra_facade::resolve_topology(const std::string & node_uri) {
}

void cassandra_facade::remove(const std::string & alias)
{
    CassStatement * statement = NULL;
    char const * delete_query = "DELETE FROM " NAMESPACE " WHERE id = ?";
    
    statement = cass_statement_new(delete_query, 1);
    cass_statement_bind_string(statement, 0, alias.c_str());

    cass_future_free(
        execute(statement));

    cass_statement_free(statement);
}

void cassandra_facade::blob_put(const std::string & alias, const std::string & content)
{
    CassStatement * statement = NULL;
    char const * insert_query = "INSERT INTO " NAMESPACE " (id, content) VALUES (?, ?)";
    
    statement = cass_statement_new(insert_query, 2);

    cass_statement_bind_string(statement, 0, alias.c_str());
    cass_statement_bind_bytes(statement, 1, reinterpret_cast<const cass_byte_t *>(content.c_str()), content.length());
    
    cass_future_free(
        execute(statement));
    cass_statement_free(statement);
}

void cassandra_facade::blob_update(const std::string & alias, const std::string & content)
{
    CassStatement * statement = NULL;
    char const * update_query = "UPDATE " NAMESPACE " SET content = ? WHERE id = ?";
    
    statement = cass_statement_new(update_query, 2);
    cass_statement_bind_bytes(statement, 0, reinterpret_cast<const cass_byte_t *>(content.c_str()), content.length());
    cass_statement_bind_string(statement, 1, alias.c_str());

    cass_future_free(
        execute(statement));

    cass_statement_free(statement);
}

std::string cassandra_facade::blob_get(const std::string & alias)
{
    CassStatement * statement = NULL;
    char const * select_query = "SELECT content FROM bench.objects WHERE id = ?";
    
    statement = cass_statement_new(select_query, 1);
    cass_statement_bind_string(statement, 0, alias.c_str());

    CassFuture * future = execute(statement);

    const CassResult* result = cass_future_get_result(future);
    CassIterator* iterator = cass_iterator_from_result(result);
    if (!cass_iterator_next(iterator))
        throw std::runtime_error("object not found: " + alias);

    const CassRow* row = cass_iterator_get_row(iterator);
    const CassValue* value = cass_row_get_column_by_name(row, "content");

    const cass_byte_t * content;
    size_t content_length;
    cass_value_get_bytes(value, &content, &content_length);

    cass_result_free(result);
    cass_iterator_free(iterator);
    cass_future_free(future);
    cass_statement_free(statement);

    return std::string(reinterpret_cast<const char*>(content), content_length);
}

CassFuture *
cassandra_facade::execute(CassStatement * statement) {
    CassError rc = CASS_OK;
    CassFuture * future = NULL;
    
    future = cass_session_execute(_session, statement);
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
