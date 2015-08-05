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
class blob_update : public test_base<blob_update>
{
public:
    explicit blob_update(bench::test_config config) : test_base(config)
    {
    }

    void run() override
    {
        std::string content = utils::create_random_string(_config.content_size);
        _qdb.call(qdb_update, _alias.c_str(), content.data(), content.size(), 0);
    }

    void cleanup() override
    {
        _qdb.call(qdb_remove, _alias.c_str());
        test_base::cleanup();
    }

    static std::string name()
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
}
}
}
