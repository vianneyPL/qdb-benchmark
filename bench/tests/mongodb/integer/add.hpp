#pragma once

#include <bench/tests/mongodb/mongodb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace mongodb
{
namespace integer
{
class add : public mongodb_test_template<add>
{
public:
    explicit add(bench::test_config config) : mongodb_test_template(config)
    {
    }
    
    void setup() override
    {
        mongodb_test_template::setup();
        _mongodb.int_put(alias(0), 0);
    }
    
    void run_iteration(unsigned long iteration)
    {
        _mongodb.int_add(alias(0), 1);
    }
    
    void cleanup() override
    {
        _mongodb.remove(alias(0));
    }
    
    static std::string name()
    {
        return "mongodb_int_add";
    }
    
    static std::string description()
    {
        return "Each thread increments an integer on one entry";
    }
    
    static bool size_dependent()
    {
        return false;
    }
};
} // namespace integer
} // namespace mongodb
} // namespace tests
} // namespace bench
