#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
namespace blob
{

class update : public qdb_test_template<update>
{
public:
    explicit update(bench::test_config config) : qdb_test_template(config)
    {
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.blob_update(alias(0), content(iteration));
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_blob_update";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_blob_update() on one entry";
    }

    static bool size_dependent()
    {
        return true;
    }

    static bool count_dependent()
    {
        return false;
    }
};

} // namespace blob
} // namespace qdb
} // namespace tests
} // namespace bench
