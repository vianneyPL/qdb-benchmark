#pragma once

#include <bench/tests/cassandra/cassandra_test_template.hpp>
#include <utils/random.hpp>

namespace bench
{
namespace tests
{
namespace cassandra
{
namespace blob
{
class put : public cassandra_test_template<put>
{
public:
    explicit put(bench::test_config config) : cassandra_test_template(config)
    {
        _content = utils::create_random_string(config.content_size);
    }

    void run_iteration(unsigned long iteration)
    {
        _cassandra.blob_put(alias(iteration), _content);
    }

    void cleanup() override
    {
        cleanup_each([=](unsigned long iteration)
                     {
                         _cassandra.remove(alias(iteration));
                     });
    }

    static std::string name()
    {
        return "cassandra_blob_put";
    }

    static std::string description()
    {
        return "Each thread repeats cassandra.insert with new ids";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _content;
};
} // namespace blob
} // namespace cassandra
} // namespace tests
} // namespace bench
