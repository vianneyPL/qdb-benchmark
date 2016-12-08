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

class get_tagged : public qdb_test_template<get_tagged>
{
public:
    get_tagged(bench::test_config config) : qdb_test_template(config), _entry_count(10)
    {
        _tag = alias(0) + "-tag";
    }

    void setup() override
    {
        qdb_test_template::setup();
        for (std::uint32_t i = 0u; i < _entry_count; ++i)
        {
            const auto entry = alias(i);
            _qdb.blob_put(entry, "content");
            _qdb.attach_tag(entry, _tag);
        }
    }

    void run_iteration(std::uint32_t iteration)
    {
        _qdb.get_tagged(_tag);
    }

    void cleanup() override
    {
        for (std::uint32_t i = 0u; i < _entry_count; ++i)
        {
            _qdb.remove(alias(i));
        }
        _qdb.remove(_tag);
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_tag_get_tagged";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_get_tagged() on a tag with 10 entries";
    }

    static bool size_dependent()
    {
        return false;
    }

private:
    std::string _tag;
    std::size_t _entry_count;
};

} // namespace tag
} // namespace qdb
} // namespace tests
} // namespace bench
