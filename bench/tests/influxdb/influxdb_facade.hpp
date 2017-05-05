#pragma once

#include <api.hpp>

#include <string>
#include <vector>

namespace bench
{
namespace tests
{
namespace influxdb
{

class influxdb_facade
{
public:
    influxdb_facade();
    ~influxdb_facade();

    void connect(const std::string & cluster_uri);

    void remove(const std::string & alias);

    void ts_col_blob_insert(const std::string & alias, const std::string & col_name, const std::string & content);
    void ts_col_double_insert(const std::string & alias,
                              const std::string & col_name,
                              const std::pair<double, idb_time_t> & point);
    void ts_col_double_inserts(const std::string & alias,
                               const std::string & col_name,
                               const std::vector<std::pair<double, idb_time_t>> & points);
    void ts_col_double_average(const std::string & alias,
                               const std::string & col_name,
                               const std::pair<idb_time_t, idb_time_t> & range);

private:
    idb::api::api m_api;
};

} // namespace influxdb
} // namespace tests
} // namespace bench
