#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
namespace hset
{
class contains : public qdb_test_template<contains>
{
public:
    explicit contains(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();

        setup_each([=](unsigned long iteration)
                   {
                       _qdb.hset_insert(alias(0), content(iteration));
                   });
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.hset_contains(alias(0), content(iteration));
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_hset_contains";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_hset_contains() on one entry";
    }

    static bool size_dependent()
    {
        return true;
    }
};
} // namespace hset
} // namespace qdb
} // namespace tests
} // namespace bench
