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
class blob_get_noalloc : public test_base<blob_get_noalloc>
{
public:
    blob_get_noalloc(bench::test_config config) : test_base(config), _buffer(config.content_size)
    {
        _content = utils::create_random_vector(config.content_size);
    }

    void setup() override
    {
        test_base::setup();
        _qdb.call(qdb_put, _alias.c_str(), _content.data(), _content.size(), 0);
    }

    void run() override
    {
        std::size_t result_size = _buffer.size();
        _qdb.call(qdb_get_noalloc, _alias.c_str(), _buffer.data(), &result_size);
        if (result_size != _buffer.size()) throw std::exception();
    }

    void cleanup() override
    {
        _qdb.call(qdb_remove, _alias.c_str());
        test_base::cleanup();
    }

    static std::string name()
    {
        return "qdb_blob_get_noalloc";
    }

    static std::string description()
    {
        return "Repeated qdb_get_noalloc() of the same entry.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::vector<char> _buffer;
    std::vector<char> _content;
};
}
}
}
