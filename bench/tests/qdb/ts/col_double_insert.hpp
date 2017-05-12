#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
namespace ts
{
class col_double_insert : public qdb_test_template<col_double_insert>
{
public:
    explicit col_double_insert(bench::test_config config) : qdb_test_template(config), _ts_size(config.content_size)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.ts_create(alias(0), {qdb_ts_column_info_t{"double_col", qdb_ts_column_double}});
    }

    void run_iteration(std::uint32_t iteration)
    {
        if (_ts_size == 1)
        {
            _qdb.ts_col_double_insert(alias(0), "double_col", qdb_timespec_t{iteration, 0},
                                      static_cast<double>(iteration));
        }
        else
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<qdb_time_t> dist_time(0, 14902061390);
            static std::uniform_real_distribution<double> dist_double(0, 10);

            std::vector<qdb_ts_double_point> points(_ts_size);
            auto timestamp = dist_time(gen);
            std::generate(points.begin(), points.end(), [&timestamp]() {
                return qdb_ts_double_point{qdb_timespec_t{++timestamp, 0}, dist_double(gen)};
            });
            _qdb.ts_col_double_inserts(alias(0), "double_col", points.data(), points.size());
        }
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_ts_col_double_insert";
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
