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
class insert : public qdb_test_template<insert>
{
public:
    explicit insert(bench::test_config config) : qdb_test_template(config)
    {
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.hset_insert(alias(0), content(iteration));
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_hset_insert";
    }

    static std::string description()
    {
        return "Call qdb_hset_insert() on one entry";
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
