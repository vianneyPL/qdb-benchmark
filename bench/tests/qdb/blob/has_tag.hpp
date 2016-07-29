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

class has_tag : public qdb_test_template<has_tag>
{
public:
    has_tag(bench::test_config config) : qdb_test_template(config)
    {
        _target_alias = alias(0) + "-target";
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.blob_put(_target_alias, "hello world!");

        setup_each([=](std::uint32_t iteration) { _qdb.add_tag(_target_alias, alias(iteration)); });
    }

    void run_iteration(std::uint32_t iteration)
    {
        _qdb.has_tag(_target_alias, alias(iteration));
    }

    void cleanup() override
    {
        _qdb.remove(_target_alias);

        cleanup_each([=](std::uint32_t iteration) { _qdb.remove(alias(iteration)); });

        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_blob_has_tag";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_has_tag() on one blob";
    }

    static bool size_dependent()
    {
        return false;
    }

private:
    std::string _target_alias;
};

} // namespace blob
} // namespace qdb
} // namespace tests
} // namespace bench
