#pragma once

#include <iostream>
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
class get : public cassandra_test_template<get>
{
public:
    explicit get(bench::test_config config) : cassandra_test_template(config)
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
        std::string content = _cassandra.blob_get(alias(0));

        if (content != _content) 
            throw std::runtime_error("content != _content");
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

private:
    std::string _content;
};
} // namespace blob
} // namespace cassandra
} // namespace tests
} // namespace bench
