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
class update : public qdb_test_template<update>
{
public:
    explicit update(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.int_put(alias(0), 0);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.int_update(alias(0), iteration);
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
    }

    static std::string name()
    {
        return "qdb_int_update";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_int_update() on one entry";
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
