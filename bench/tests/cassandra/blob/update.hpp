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
class update : public cassandra_test_template<update>
{
public:
    explicit update(bench::test_config config) : cassandra_test_template(config)
    {
    }

    void setup() override
    {
        cassandra_test_template::setup();
        _cassandra.blob_put(alias(0), content(0));
    }

    void run_iteration(std::uint32_t iteration)
    {
        _cassandra.blob_update(alias(0), content(iteration));
    }

    void cleanup() override
    {
        _cassandra.remove(alias(0));
    }

    static std::string name()
    {
        return "cassandra_blob_update";
    }

    static std::string description()
    {
        return "Each thread repeats cassandra.update on a single entry";
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
