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
class get_noalloc : public qdb_test_template<get_noalloc>
{
public:
    get_noalloc(bench::test_config config) : qdb_test_template(config), _buffer(config.content_size, 0)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.blob_put(alias(0), content(0));
    }

    void run_iteration(std::uint32_t iteration)
    {
        _qdb.blob_get_noalloc(alias(0), _buffer);
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_blob_get_noalloc";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_blob_get_noalloc() on one entry";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _buffer;
};
} // namespace blob
} // namespace qdb
} // namespace tests
} // namespace bench
