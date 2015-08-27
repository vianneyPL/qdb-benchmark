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
class blob_remove : public test_base<blob_remove>
{
public:
    explicit blob_remove(bench::test_config config) : test_base(config)
    {
        _content = utils::create_random_string(config.content_size);
        perform_per_iteration_setup();
    }

    void setup_iteration(unsigned long iteration)
    {
        _qdb.blob_put(get_alias(iteration), _content);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.remove(get_alias(iteration));
    }

    static std::string name()
    {
        return "qdb_blob_remove";
    }

    static std::string description()
    {
        return "Call qdb_remove() on blob entries.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _content;

    std::string get_alias(long long iteration) const
    {
        return _alias + std::to_string(iteration);
    }
};
}
}
}
