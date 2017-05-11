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
    explicit col_double_insert(bench::test_config config)
        : influxdb_test_template(config), _ts_size(config.content_size)
    {
    }

    void setup() override
    {
        influxdb_test_template::setup();
    }

    void run_iteration(std::uint32_t iteration)
    {
        if (_ts_size == 1)
        {
            _influxdb.ts_col_double_insert(
                alias(0), "double_col", timepoint{static_cast<double>(iteration), static_cast<idb_time_t>(iteration)});
        }
        else
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<idb_time_t> distTime(0, 14902061390);
            static std::uniform_real_distribution<double> distDouble(0, 10);

            std::vector<timepoint> points(_ts_size);
            auto timestamp = distTime(gen);
            std::generate(points.begin(), points.end(), [&timestamp]() {
                return timepoint{distDouble(gen), ++timestamp};
            });
            _influxdb.ts_col_double_inserts(alias(0), "double_col", points);
        }
    }

    void cleanup() override
    {
        _influxdb.cleanup();
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
        return true;
    }

private:
    const size_t _ts_size;
};
} // namespace ts
} // namespace qdb
} // namespace tests
} // namespace bench
