#pragma once

#include <bench/tests/qdb_test_base.hpp>
#include <utils/random.hpp>

#include <qdb/queue.h>

namespace bench {
namespace tests {

class qdb_queue_push_back : public qdb_test_base<qdb_queue_push_back>
{
public:
    explicit qdb_queue_push_back(bench::test_config config)
        : qdb_test_base(config)
    {
    }

    void run() override
    {
        std::string content = utils::create_random_string(_config.content_size);

        qdb_call(::qdb_queue_push_back, _alias.c_str(), content.data(), content.size());
    }

    ~qdb_queue_push_back() override
    {        
        qdb_call(qdb_remove, _alias.c_str());
    }

    static std::string id() 
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

}}