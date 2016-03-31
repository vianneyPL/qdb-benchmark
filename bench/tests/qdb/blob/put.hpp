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

class put : public qdb_test_template<put>
{
public:
    explicit put(bench::test_config config) : qdb_test_template(config)
    {
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.blob_put(alias(iteration), content(iteration));
    }

    void cleanup() override
    {
        cleanup_each([=](unsigned long iteration) { _qdb.remove(alias(iteration)); });
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_blob_put";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_blob_put() with new aliases";
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
