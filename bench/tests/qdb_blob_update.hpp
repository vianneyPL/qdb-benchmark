#pragma once

#include <bench/tests/qdb_test_base.hpp>
#include <utils/random.hpp>

namespace bench {
namespace tests {

class qdb_blob_update : public qdb_test_base<qdb_blob_update>
{
public:
    explicit qdb_blob_update(bench::test_config config)
        : qdb_test_base(config)
    {
    }

    void run() override
    {
        std::string content = utils::create_random_string(_config.content_size);

        qdb_call(qdb_update, _alias.c_str(), content.data(), content.size(), 0);
    }

    ~qdb_blob_update() override
    {        
        qdb_call(qdb_remove, _alias.c_str());
    }

    static std::string id() 
    {
        return "qdb_blob_update";
    }

    static std::string description() 
    {
        return "Repeated qdb_update() of the same entry.";
    }

    static bool size_dependent() 
    {
        return true;
    }
};

}}