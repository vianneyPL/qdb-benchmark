#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>
#include <utils/random.hpp>

#include <qdb/blob.h>

namespace bench
{
namespace tests
{
namespace qdb
{
class blob_get_noalloc : public qdb_test_template<blob_get_noalloc>
{
public:
    blob_get_noalloc(bench::test_config config)
        : qdb_test_template(config), _buffer(config.content_size, 0)
    {
        _alias = get_alias(0); // only one alias is needed
        _content = utils::create_random_string(config.content_size);
    }

    void setup() override
    {
        qdb_test_template::setup();
        _qdb.blob_put(_alias, _content);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.blob_get_noalloc(_alias, _buffer);
        if (_content.size() != _buffer.size()) throw std::exception();
    }

    void cleanup() override
    {
        _qdb.remove(_alias);
    }

    static std::string name()
    {
        return "qdb_blob_get_noalloc";
    }

    static std::string description()
    {
        return "Call qdb_get_noalloc() on one entry.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _alias;
    std::string _buffer;
    std::string _content;
};
}
}
}
