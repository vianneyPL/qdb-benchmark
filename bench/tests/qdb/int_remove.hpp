#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
class int_remove : public qdb_test_template<int_remove>
{
public:
    explicit int_remove(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();

        setup_each([=](unsigned long iteration)
                   {
                       _alias.set_watermark(iteration);
                       _qdb.int_put(_alias, 42);
                   });
    }

    void run_iteration(unsigned long iteration)
    {
        _alias.set_watermark(iteration);
        _qdb.remove(_alias);
    }

    static std::string name()
    {
        return "qdb_int_remove";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_remove() on integer entries";
    }

    static bool size_dependent()
    {
        return false;
    }
};
}
}
}
