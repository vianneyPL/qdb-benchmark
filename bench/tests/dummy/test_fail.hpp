#pragma once

#include <bench/tests/common/test_template.hpp>

#include <thread>

namespace bench
{
namespace tests
{
namespace dummy
{
class test_fail : public test_template<test_fail>
{
public:
    test_fail(bench::test_config config) : test_template(config)
    {
    }

    void run_iteration(std::uint32_t iteration)
    {
        throw std::runtime_error("This exception has been intentionally thrown during test.");
    }

    static std::string name()
    {
        return "dummy_test_fail";
    }

    static std::string description()
    {
        return "Throws in test";
    }

    static bool size_dependent()
    {
        return false;
    }
};
}
}
}
