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
class pop_front : public qdb_test_template<pop_front>
{
public:
    explicit pop_front(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();

        setup_each([&](unsigned long iteration)
                   {
                       _qdb.deque_push_front(alias(0), content(iteration));
                   });
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.deque_pop_front(alias(0));
    }

    static std::string name()
    {
        return "qdb_deque_pop_front";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_deque_pop_front() on a queue";
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
