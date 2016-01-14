#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
namespace tag
{
class add_blob : public qdb_test_template<add_blob>
{
public:
    add_blob(bench::test_config config) : qdb_test_template(config)
    {
        _tag = alias(0) + "-tag";
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
        _qdb.add_tag(alias(iteration), _tag);
    }

    void cleanup() override
    {
        _qdb.remove(_tag);
        cleanup_each([=](unsigned long iteration)
                     {
                         _qdb.remove(alias(iteration));
                     });
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_tag_add_blob";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_add_tag() on many blobs";
    }

    static bool size_dependent()
    {
        return false;
    }

private:
    std::string _tag;
};
} // namespace tag
} // namespace qdb
} // namespace tests
} // namespace bench
