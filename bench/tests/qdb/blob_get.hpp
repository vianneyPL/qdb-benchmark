#pragma once

#include <bench/tests/qdb/test_base.hpp>
#include <utils/random.hpp>

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
        std::vector<char> content = utils::create_random_vector(config.content_size);
        _qdb.call(qdb_put, _alias.c_str(), content.data(), content.size(), 0);
    }

    void run() override
    {
        const char * content;
        std::size_t content_size;
        _qdb.call(qdb_get, _alias.c_str(), &content, &content_size);
        if (content_size != _config.content_size)
            throw std::exception();
        _qdb.free_buffer(content);
    }

    ~blob_get() override
    {
        _qdb.call(qdb_remove, _alias.c_str());
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
};
}
}
}
