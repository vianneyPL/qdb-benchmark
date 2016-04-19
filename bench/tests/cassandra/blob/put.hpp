#pragma once

#include <bench/tests/cassandra/cassandra_test_template.hpp>

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
    }

    void run_iteration(std::uint32_t iteration)
    {
        _cassandra.blob_put(alias(iteration), content(iteration));
    }

    void cleanup() override
    {
        cleanup_each([=](std::uint32_t iteration) { _cassandra.remove(alias(iteration)); });
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
};
} // namespace blob
} // namespace cassandra
} // namespace tests
} // namespace bench
