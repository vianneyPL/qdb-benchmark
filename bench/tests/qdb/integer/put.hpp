#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
namespace integer
{
class put : public qdb_test_template<put>
{
public:
    explicit put(bench::test_config config) : qdb_test_template(config)
    {
    }

    void run_iteration(std::uint32_t iteration)
    {
        _qdb.int_put(alias(iteration), 42);
    }

    void cleanup() override
    {
        cleanup_each([&](std::uint32_t iteration) { _qdb.remove(alias(iteration)); });
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_int_put";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_put() with new aliases";
    }

    static bool size_dependent()
    {
        return false;
    }
};
} // namespace integer
} // namespace qdb
} // namespace tests
} // namespace bench
