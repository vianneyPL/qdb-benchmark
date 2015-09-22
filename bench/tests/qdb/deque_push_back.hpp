#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>
#include <utils/random.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
class deque_push_back : public qdb_test_template<deque_push_back>
{
public:
    explicit deque_push_back(bench::test_config config) : qdb_test_template(config)
    {
        _alias = get_alias(0); // only one alias is needed
        _content = utils::create_random_string(config.content_size);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.deque_push_back(_alias, _content);
    }

    void cleanup() override
    {
        _qdb.remove(_alias);
    }

    static std::string name()
    {
        return "qdb_deque_push_back";
    }

    static std::string description()
    {
        return "Call qdb_deque_push_back() on one entry.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _alias;
    std::string _content;
};
}
}
}
