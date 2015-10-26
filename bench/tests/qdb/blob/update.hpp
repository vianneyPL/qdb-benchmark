#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>
#include <utils/random.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
namespace blob
{
class update : public qdb_test_template<update>
{
public:
    explicit update(bench::test_config config) : qdb_test_template(config)
    {
        _content = utils::create_random_string(config.content_size);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.blob_update(alias(0), _content);
    }

    void cleanup() override
    {
        _qdb.remove(alias(0));
    }

    static ::std::string name()
    {
        return "qdb_blob_update";
    }

    static ::std::string description()
    {
        return "Each thread repeats qdb_blob_update() on one entry";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    ::std::string _content;
};
} // namespace blob
} // namespace qdb
} // namespace tests
} // namespace bench
