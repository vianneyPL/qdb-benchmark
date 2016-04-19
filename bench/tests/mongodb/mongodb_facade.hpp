#pragma once

#include <mongo/client/dbclient.h>
#include <string>
#include <vector>

namespace bench
{
namespace tests
{
namespace mongodb
{
class mongodb_facade
{
public:
    mongodb_facade();
    ~mongodb_facade();

    void connect(const std::string & cluster_uri);

    static mongo::BSONObj server_status(const std::string & node_uri);
    static mongo::BSONObj db_status(const std::string & node_uri);
    static std::vector<std::string> resolve_topology(const std::string & node_uri);

    void remove(const std::string & alias);

    void blob_put(const std::string & alias, const std::string & content);
    void blob_update(const std::string & alias, const std::string & content);
    std::string blob_get(const std::string & alias);

    std::int64_t int_add(const std::string & alias, std::int64_t value);
    void int_put(const std::string & alias, std::int64_t value);
    void int_update(const std::string & alias, std::int64_t value);
    std::int64_t int_get(const std::string & alias);

private:
    mongo::DBClientConnection _conn;
};

} // namespace mongodb
} // namespace tests
} // namespace bench
