#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

#include <qdb/integer.h>

namespace bench
{
namespace tests
{
namespace qdb
{
class int_get : public qdb_test_template<int_get>
{
public:
    explicit int_get(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.int_put(_alias, 42);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.int_get(_alias);
    }

    void cleanup() override
    {
        _qdb.remove(_alias);
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
};
}
}
}
