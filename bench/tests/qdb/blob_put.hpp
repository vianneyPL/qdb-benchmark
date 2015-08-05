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
class blob_put : public test_base<blob_put>
{
public:
    explicit blob_put(bench::test_config config) : test_base(config), _iterations(0)
    {
        _content = utils::create_random_string(_config.content_size);
    }

    void run() override
    {
        std::string alias = get_alias(_iterations + 1);
        _qdb.call(qdb_put, alias.c_str(), _content.data(), _content.size(), 0);
        _iterations++;
    }

    void cleanup() override
    {
        while (_iterations > 0)
        {
            std::string alias = get_alias(_iterations);
            _qdb.call(qdb_remove, alias.c_str());
            _iterations--;
        }
        test_base::cleanup();
    }

    static std::string name()
    {
        return "qdb_blob_put";
    }

    static std::string description()
    {
        return "Repeated qdb_put() of new entries.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string get_alias(long long iteration) const
    {
        return _alias + std::to_string(iteration);
    }

    long long _iterations;
    std::string _content;
};
}
}
}
