#pragma once

#include <bench/tests/qdb/test_base.hpp>
#include <utils/random.hpp>

#include <qdb/queue.h>

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
    }

    void run() override
    {
        std::string content = utils::create_random_string(_config.content_size);

        _qdb.call(::qdb_queue_push_back, _alias.c_str(), content.data(), content.size());
    }

    ~queue_push_back() override
    {
        _qdb.call(qdb_remove, _alias.c_str());
    }

    static std::string name()
    {
        return "qdb_queue_push_back";
    }

    static std::string description()
    {
        return "Repeated qdb_queue_push_back() to the same entry.";
    }

    static bool size_dependent()
    {
        return true;
    }
};
}
}
}
