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
        std::vector<char> content = utils::create_random_vector(config.content_size);
        _qdb.call(qdb_put, _alias.c_str(), content.data(), content.size(), 0);
    }

    void run() override
    {
        std::size_t content_size = _config.content_size;
        _qdb.call(qdb_get_noalloc, _alias.c_str(), _buffer.data(), &content_size);
        if (content_size != _config.content_size) throw std::exception();
    }

    ~blob_get_noalloc() override
    {
        _qdb.call(qdb_remove, _alias.c_str());
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
};
}
}
}
