#include <iostream>

#include <boost/algorithm/string.hpp>
#include <bench/tests/mongodb/mongodb_facade.hpp>
#include <mongo/bson/bson.h>

#define NAMESPACE "bench.objects"

// Calls MongoDB function, checks for error and discards result
#define CHECK_ERROR(func, conn, ...)         \
    conn.func(__VA_ARGS__);                  \
                                             \
    std::string error = conn.getLastError(); \
    if (error != "") throw std::runtime_error(#func + error);

// Calls MongoDB function, checks for error and store result in `result`
#define CHECK_ERROR_STORE(func, conn, result, ...) \
    auto result = conn.func(__VA_ARGS__);          \
                                                   \
    std::string error = conn.getLastError();       \
    if (error != "") throw std::runtime_error(#func + error);

using namespace bench::tests::mongodb;

mongodb_facade::mongodb_facade()
{
}

mongodb_facade::~mongodb_facade()
{
}

void
mongodb_facade::connect(const std::string & cluster_uri) {
    _conn.connect(cluster_uri);    
}

/* static */ mongo::BSONObj mongodb_facade::server_status(const std::string & node_uri) {
    mongo::DBClientConnection conn;
    conn.connect(node_uri);

    mongo::BSONObj serverStatus;
    
    if (!conn.runCommand("bench", BSON("serverStatus" << 1), serverStatus)) {
        throw std::runtime_error("node_status: serverStatus");
    }

    return BSON("server" << serverStatus << "db" << mongodb_facade::db_status(node_uri));
}

/* static */ mongo::BSONObj mongodb_facade::db_status(const std::string & node_uri) {
    mongo::DBClientConnection conn;
    conn.connect(node_uri);

    mongo::BSONObj dbStats;
    if (!conn.runCommand("bench", BSON("dbStats" << 1), dbStats)) {
        throw std::runtime_error("node_status: dbStats");
    }

    return dbStats;    
}


/* static */ std::vector<std::string> mongodb_facade::resolve_topology(const std::string & node_uri) {
    mongo::DBClientConnection conn;
    conn.connect(node_uri);

    /* 
       Our `node_uri` can be any of the following:
       
       * an entry to a `mongos` instance, a sharded cluster;
       * an entry to a replica set;
       * a single node configuration.
       
       We are going to probe for what kind of configuration we are
       dealing with by executing the relevant admin commands, and
       based on those responses resolve the entire topology.
    */

    mongo::BSONObj response;
    
    std::vector<std::string> result;    

    if (conn.runCommand("admin", BSON("listShards" << 1), response)) {
        // We are in sharded cluster.

        for (mongo::BSONElement const & member : response["shards"].Array()) {
            // Member can be either a replica set, which looks like
            // `rs0/1.2.3.4:1234,4.3.2.1:4321`, or it is a regular
            // host, which looks like `1.2.3.4:1234`.
            std::string host = member["host"].String();

            std::vector<std::string> tokens;
            boost::split(tokens, host, boost::is_any_of("/"));

            if (tokens.size() == 1) {
                // A regular host
                result.push_back(tokens.at(0));                
            } else if (tokens.size() == 2) {
                std::vector<std::string> hosts;

                boost::split(hosts, tokens.at(1), boost::is_any_of(","));
                
                std::copy(hosts.begin(), hosts.end(), 
                          std::back_insert_iterator<std::vector<std::string>>(result));                
            } else {
                throw std::runtime_error("Invalid host: " + host);
            }
        }
        
    } else if (conn.runCommand("admin", BSON("replSetGetStatus" << 1), response)) {
        // A replica set has been configured.
        for (mongo::BSONElement const & member : response["members"].Array()) {
            result.push_back(member["name"].String());
        }

    } else {
        // Single node configuration.
        result.push_back(node_uri);        
    }

    return result;    
}

void mongodb_facade::remove(const std::string & alias)
{
    CHECK_ERROR(remove, _conn, NAMESPACE, MONGO_QUERY("_id" << alias), true, NULL);
}

void mongodb_facade::blob_put(const std::string & alias, const std::string & content)
{
    CHECK_ERROR(insert, _conn, NAMESPACE, BSON("_id" << alias << "content" << content));
}

void mongodb_facade::blob_update(const std::string & alias, const std::string & content)
{
    CHECK_ERROR(findAndModify, _conn, NAMESPACE, BSON("_id" << alias), BSON("content" << content),
                false, true);
}

std::string mongodb_facade::blob_get(const std::string & alias)
{
    CHECK_ERROR_STORE(query, _conn, cursor, NAMESPACE, MONGO_QUERY("_id" << alias));

    return cursor->next().getField("content").String();
}

void mongodb_facade::int_put(const std::string & alias, std::int64_t value)
{
    CHECK_ERROR(insert, _conn, NAMESPACE,
                BSON("_id" << alias << "num" << static_cast<long long>(value)));
}

std::int64_t mongodb_facade::int_add(const std::string & alias, std::int64_t value)
{
    CHECK_ERROR_STORE(findAndModify, _conn, obj, NAMESPACE, BSON("_id" << alias),
                      BSON("$inc" << BSON("num" << static_cast<long long>(value))), false, true);

    return obj.getField("num").Long();
}
