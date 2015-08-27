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
    explicit blob_update(bench::test_config config)
        : test_base(config), _content_size(config.content_size)
    {
    }

    void run_iteration(unsigned long iteration)
    {
        std::string content = utils::create_random_string(_content_size);
        _qdb.blob_update(_alias, content);
    }

    ~blob_update()
    {
        _qdb.remove(_alias);
    }

    static std::string name()
    {
        return "qdb_blob_update";
    }

    static std::string description()
    {
        return "Call qdb_update() on one entry.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    unsigned long _content_size;
};
}
}
}
