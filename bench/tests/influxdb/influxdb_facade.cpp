#include <bench/tests/influxdb/influxdb_facade.hpp>
#include <cppformat/format.h>
#include <exception>
#include <iostream>

using api = idb::api::api;
using tag = idb::api::measurement::tag;
using str_field = idb::api::measurement::field<std::string>;
using double_field = idb::api::measurement::field<double>;
using int_field = idb::api::measurement::field<int>;
using measurement = idb::api::measurement::measurement;
using measurements = idb::api::measurement::measurements;

#define NAMESPACE "bench.objects"

using namespace bench::tests::influxdb;

influxdb_facade::influxdb_facade()
{
    //  m_api = api("http://localhost:8086", "benchmark");
}

influxdb_facade::~influxdb_facade()
{
    m_api.drop();
}

void influxdb_facade::connect(const std::string & cluster_uri)
{
    m_api.create();
    // _async_api.create();
}

void influxdb_facade::remove(const std::string & alias)
{
    try
    {
        m_api.drop(measurement(alias));
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void influxdb_facade::ts_col_blob_insert(const std::string & alias,
                                         const std::string & col_name,
                                         const std::string & content)
{
    try
    {
        measurement mes(alias);
        mes << str_field(col_name, content);
        m_api.create(mes);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void influxdb_facade::ts_col_double_insert(const std::string & alias,
                                           const std::string & col_name,
                                           const std::pair<double, idb_time_t> & point)
{
    try
    {
        measurement mes(alias);
        mes << double_field(col_name, point.first) << point.second;
        m_api.create(mes);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void influxdb_facade::ts_col_double_inserts(const std::string & alias,
                                            const std::string & col_name,
                                            const std::vector<std::pair<double, idb_time_t>> & points)
{
    std::pair<double, idb_time_t> current_point;
    try
    {
        measurements measures;
        for (const auto & point : points)
        {
            measurement mes(alias);
            mes << double_field(col_name, point.first) << point.second;
            measures << mes;
        }
        m_api.create(measures);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void influxdb_facade::ts_col_double_average(const std::string & alias,
                                            const std::string & col_name,
                                            const std::pair<idb_time_t, idb_time_t> & range)
{
    try
    {
        std::string what = fmt::format("MEAN(\"{}\")", alias);
        std::string from = fmt::format("\"{}\"", col_name);
        std::string where = fmt::format("time >= '{}' AND time < '{}'", range.first, range.second);
        m_api.select(what, from, where);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}
