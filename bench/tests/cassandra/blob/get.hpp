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
class get : public cassandra_test_template<get>
{
public:
    explicit get(bench::test_config config) : cassandra_test_template(config)
    {
    }

    void setup() override
    {
        cassandra_test_template::setup();
        _cassandra.blob_put(alias(0), content(0));
    }

    void run_iteration(unsigned long iteration)
    {
        _cassandra.blob_get(alias(0));
    }

    void cleanup() override
    {
        _cassandra.remove(alias(0));
    }

    static std::string name()
    {
        return "cassandra_blob_get";
    }

    static std::string description()
    {
        return "Each thread repeats cassandra.query on a single entry";
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
