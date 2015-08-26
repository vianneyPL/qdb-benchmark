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
        _content = utils::create_random_string(_config.content_size);
        _qdb.blob_put(_alias, _content);
    }

    void run_iteration()
    {
        auto content = _qdb.blob_get(_alias);
        if (content.size() != _content.size()) throw std::exception();
    }

    ~blob_get() override
    {
        _qdb.remove(_alias);
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
    std::string _content;
};
}
}
}
