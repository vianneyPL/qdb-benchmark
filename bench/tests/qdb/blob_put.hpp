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
    explicit blob_put(bench::test_config config) : test_base(config)
    {
        _content = utils::create_random_string(config.content_size);
    }

    ~blob_put()
    {
        perform_per_iteration_cleanup();
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.blob_put(get_alias(iteration), _content);
    }

    void cleanup_iteration(unsigned long iteration)
    {
        _qdb.remove(get_alias(iteration));
    }

    static std::string name()
    {
        return "qdb_blob_put";
    }

    static std::string description()
    {
        return "Call qdb_put().";
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

    std::string _content;
};
}
}
}