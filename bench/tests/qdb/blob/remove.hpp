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
class remove : public qdb_test_template<remove>
{
public:
    explicit remove(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();

        setup_each([=](unsigned long iteration)
                   {
                       _qdb.blob_put(alias(iteration), content(iteration));
                   });
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.remove(alias(iteration));
    }

    static std::string name()
    {
        return "qdb_blob_remove";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_remove() on blob entries";
    }

    static bool size_dependent()
    {
        return true;
    }
};
} // namespace blob
} // namespace qdb
} // namespace tests
} // namespace bench
