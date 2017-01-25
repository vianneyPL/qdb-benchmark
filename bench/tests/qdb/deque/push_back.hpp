#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
namespace deque
{

class push_back : public qdb_test_template<push_back>
{
public:
    explicit push_back(bench::test_config config) : qdb_test_template(config)
    {
    }

    void run_iteration(std::uint32_t iteration)
    {
        _qdb.deque_push_back(alias(0), content(iteration));
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_deque_push_back";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_deque_push_back() on a queue";
    }

    static bool size_dependent()
    {
        return true;
    }
};

} // namespace deque
} // namespace qdb
} // namespace tests
} // namespace bench
