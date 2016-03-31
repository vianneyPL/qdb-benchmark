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

class get : public qdb_test_template<get>
{
public:
    explicit get(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.int_put(alias(0), 42);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.int_get(alias(0));
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_int_get";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_int_get() on one entry";
    }

    static bool size_dependent()
    {
        return false;
    }

    static bool count_dependent()
    {
        return false;
    }
};

} // namespace integer
} // namespace qdb
} // namespace tests
} // namespace bench
