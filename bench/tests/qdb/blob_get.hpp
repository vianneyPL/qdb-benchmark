#pragma once

#include <bench/tests/qdb/test_base.hpp>
#include <utils/random.hpp>

#include <qdb/blob.h>

namespace bench
{
namespace tests
{
namespace qdb
{
class blob_get : public test_base<blob_get>
{
public:
    blob_get(bench::test_config config) : test_base(config)
    {
        _content = utils::create_random_vector(_config.content_size);
    }

    void setup() override
    {
        test_base::setup();
        _qdb.call(qdb_put, _alias.c_str(), _content.data(), _content.size(), 0);
    }

    void run() override
    {
        const char * result;
        std::size_t result_size;
        _qdb.call(qdb_get, _alias.c_str(), &result, &result_size);
        if (result_size != _content.size()) throw std::exception();
        _qdb.free_buffer(result);
    }

    void cleanup() override
    {
        _qdb.call(qdb_remove, _alias.c_str());
        test_base::cleanup();
    }

    static std::string name()
    {
        return "qdb_blob_get";
    }

    static std::string description()
    {
        return "Repeated qdb_get() of the same entry.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::vector<char> _content;
};
}
}
}
