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
class update : public cassandra_test_template<update>
{
public:
    explicit update(bench::test_config config) : cassandra_test_template(config)
    {
        _content = utils::create_random_string(config.content_size);
    }

    void setup() override
    {
        cassandra_test_template::setup();
        _cassandra.blob_put(alias(0), _content);
    }

    void run_iteration(unsigned long iteration)
    {
        _cassandra.blob_update(alias(0), _content);
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

private:
    std::string _content;
};
} // namespace blob
} // namespace cassandra
} // namespace tests
} // namespace bench
