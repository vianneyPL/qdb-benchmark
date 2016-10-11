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

class attach_blob : public qdb_test_template<attach_blob>
{
public:
    attach_blob(bench::test_config config) : qdb_test_template(config)
    {
        _tag = alias(0) + "-tag";
    }

    void setup() override
    {
        qdb_test_template::setup();
        setup_each([=](std::uint32_t iteration) { _qdb.blob_put(alias(iteration), "hello world!"); });
    }

    void run_iteration(std::uint32_t iteration)
    {
        _qdb.attach_tag(alias(iteration), _tag);
    }

    void cleanup() override
    {
        _qdb.remove(_tag);
        cleanup_each([=](std::uint32_t iteration) { _qdb.remove(alias(iteration)); });
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_tag_attach_blob";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_attach_tag() on many blobs";
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
