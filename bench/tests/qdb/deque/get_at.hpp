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

class get_at : public qdb_test_template<get_at>
{
public:
    explicit get_at(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();

        setup_each([&](std::uint32_t iteration) { _qdb.deque_push_back(alias(0), content(iteration)); });
    }

    void run_iteration(std::uint32_t iteration)
    {
        _qdb.deque_get_at(alias(0), iteration);
    }

    static std::string name()
    {
        return "qdb_deque_get_at";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_deque_get_at() on a queue";
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
