#pragma once

#include <bench/tests/influxdb/influxdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace influxdb
{
namespace ts
{
class col_double_insert : public influxdb_test_template<col_double_insert>
{
public:
    explicit col_double_insert(bench::test_config config) : influxdb_test_template(config)
    {
    }

    void setup() override
    {
        influxdb_test_template::setup();
    }

    void run_iteration(std::uint32_t iteration)
    {
        _influxdb.ts_col_double_insert(
            alias(0), "double_col", std::make_pair(static_cast<double>(iteration), static_cast<idb_time_t>(iteration)));
    }

    void cleanup() override
    {
        _influxdb.remove(alias(0));
        influxdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "influxdb_ts_col_double_insert";
    }

    static std::string description()
    {
        return "Each thread inserts a double point in the same time series column";
    }

    static bool size_dependent()
    {
        return false;
    }
};
} // namespace ts
} // namespace qdb
} // namespace tests
} // namespace bench
