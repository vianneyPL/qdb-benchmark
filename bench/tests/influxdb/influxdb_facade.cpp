#include <bench/tests/influxdb/influxdb_facade.hpp>
#include <cppformat/ostream.h>
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
        std::cerr << __FUNCTION__ << " failed.\n";
        std::cerr << "Tried (alias:" << alias << ")\n";
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
        std::cerr << __FUNCTION__ << " failed.\n";
        std::cerr << "Tried (alias:" << alias << ") (col_name:" << col_name << ") (content:" << content << ")\n";
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
        std::cerr << __FUNCTION__ << " failed.\n";
        std::cerr << "Tried (alias:" << alias << ") (col_name:" << col_name << ") (content:" << point.first << "-"
                  << point.second << ")\n";
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
        std::cerr << __FUNCTION__ << " failed.\n";
        std::cerr << "Tried (alias:" << alias << ") (col_name:" << col_name << ") (content:" << current_point.first
                  << "-" << current_point.second << ")\n";
        std::rethrow_exception(std::current_exception());
    }
}

void influxdb_facade::ts_col_double_average(const std::string & alias,
                                            const std::string & col_name,
                                            const std::pair<idb_time_t, idb_time_t> & range)
{
    try
    {
        fmt::MemoryWriter what;
        what << "MEAN(\"" << alias << "\")";
        fmt::MemoryWriter from;
        from << "\"" << col_name << "\"";
        fmt::MemoryWriter where;
        where << "time >= '" << range.first << "' AND time < '" << range.second << "'";
        m_api.select(what.str(), from.str(), where.str());
    }
    catch (...)
    {
        std::cerr << __FUNCTION__ << " failed.\n";
        std::rethrow_exception(std::current_exception());
    }
}
