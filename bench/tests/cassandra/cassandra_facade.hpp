#pragma once

#include <cassandra.h>
#include <string>
#include <vector>

namespace bench
{
namespace tests
{
namespace cassandra
{

class cassandra_facade
{
public:
    cassandra_facade();
    ~cassandra_facade();

    void connect(const std::string & cluster_uri);
    static std::vector<std::string> resolve_topology(const std::string & node_uri);

    void remove(const std::string & alias);

    void blob_put(const std::string & alias, const std::string & content);
    void blob_update(const std::string & alias, const std::string & content);
    std::string blob_get(const std::string & alias);

private:
    static CassFuture * execute(CassSession * session, CassStatement * statement);

private:
    CassCluster * _cluster;
    CassSession * _session;
};

} // namespace cassandra
} // namespace tests
} // namespace bench
