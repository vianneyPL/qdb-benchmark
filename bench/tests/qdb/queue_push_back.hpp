#pragma once

#include <bench/tests/qdb/test_base.hpp>
#include <utils/random.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
class queue_push_back : public test_base<queue_push_back>
{
public:
    explicit queue_push_back(bench::test_config config) : test_base(config)
    {
        _content = utils::create_random_string(config.content_size);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.queue_push_back(_alias, _content);
    }

    ~queue_push_back()
    {
        _qdb.remove(_alias);
    }

    static std::string name()
    {
        return "qdb_queue_push_back";
    }

    static std::string description()
    {
        return "Call qdb_queue_push_back() on one entry.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _content;
};
}
}
}
