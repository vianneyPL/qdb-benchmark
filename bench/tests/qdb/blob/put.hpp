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
class put : public qdb_test_template<put>
{
public:
    explicit put(bench::test_config config) : qdb_test_template(config)
    {
        _content = utils::create_random_string(config.content_size);
    }

    void run_iteration(unsigned long iteration)
    {
        _qdb.blob_put(alias(iteration), _content);
    }

    void cleanup() override
    {
        cleanup_each([=](unsigned long iteration)
                     {
                         _qdb.remove(alias(iteration));
                     });
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_blob_put";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_blob_put() with new aliases";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _content;
};
} // namespace blob
} // namespace qdb
} // namespace tests
} // namespace bench
