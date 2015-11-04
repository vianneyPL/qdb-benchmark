#pragma once

#include <mongo/client/dbclient.h>

namespace utils
{
class mongodb_wrapper
{
public:
    mongodb_wrapper();
    ~mongodb_wrapper();

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
}
