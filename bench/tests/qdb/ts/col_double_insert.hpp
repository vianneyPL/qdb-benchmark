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
    explicit col_double_insert(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.ts_create(alias(0), {qdb_ts_column_info_t{"double_col", qdb_ts_column_double}});
    }

    void run_iteration(std::uint32_t iteration)
    {
        qdb_timespec_t ts;

        ts.tv_sec = iteration;
        ts.tv_nsec = 0;

        _qdb.ts_col_double_insert(alias(0), "double_col", ts, static_cast<double>(iteration));
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
        return false;
    }
};
} // namespace ts
} // namespace qdb
} // namespace tests
} // namespace bench
