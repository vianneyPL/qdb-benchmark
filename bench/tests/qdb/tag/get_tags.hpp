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

class get_tags : public qdb_test_template<get_tags>
{
public:
    get_tags(bench::test_config config) : qdb_test_template(config), _tag_count(10)
    {
        _entry = alias(0) + "-entry";
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.blob_put(_entry, "content");
        for (std::uint32_t i = 0u; i < _tag_count; ++i)
        {
            _qdb.attach_tag(_entry, alias(i));
        }
    }

    void run_iteration(std::uint32_t /*iteration*/)
    {
        _qdb.get_tags(_entry);
    }

    void cleanup() override
    {
        for (std::uint32_t i = 0u; i < _tag_count; ++i)
        {
            _qdb.detach_tag(_entry, alias(i));
        }
        _qdb.remove(_entry);
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_tag_get_tags";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_get_tags() on a blob with 10 tags";
    }

    static bool size_dependent()
    {
        return false;
    }

private:
    std::string _entry;
    std::size_t _tag_count;
};

} // namespace tag
} // namespace qdb
} // namespace tests
} // namespace bench
