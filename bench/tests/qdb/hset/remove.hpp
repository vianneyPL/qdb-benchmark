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
class remove : public qdb_test_template<remove>
{
public:
    explicit remove(bench::test_config config)
        : qdb_test_template(config), _content_count(config.content_count), _content(sizeof(std::uint64_t))
    {
    }

    void setup() override
    {
        qdb_test_template::setup();

        setup_each([=](unsigned long iteration) {
            auto a = alias(iteration);
            for (auto i = 0u; i < _content_count; ++i)
            {
                _content.set_watermark(i);
                _qdb.hset_insert(a, _content);
            }
        });
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.remove(alias(iteration));
    }

    static std::string name()
    {
        return "qdb_hset_remove";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_remove() on hset entries";
    }

    static bool size_dependent()
    {
        return false;
    }

    static bool count_dependent()
    {
        return true;
    }

private:
    std::size_t _content_count;
    utils::unique_content _content;
};

} // namespace hset
} // namespace qdb
} // namespace tests
} // namespace bench
