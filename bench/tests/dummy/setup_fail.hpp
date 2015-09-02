#pragma once

#include <bench/tests/test_template.hpp>

#include <thread>

namespace bench
{
namespace tests
{
namespace dummy
{
class setup_fail : public test_template<setup_fail>
{
public:
    setup_fail(bench::test_config config) : test_template(config)
    {
    }

    void setup() override
    {
        throw std::runtime_error("This exception has been intentionally thrown during setup.");
    }

    void run_iteration(unsigned long iteration)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    static std::string name()
    {
        return "dummy_setup_fail";
    }

    static std::string description()
    {
        return "Throws in setup";
    }

    static bool size_dependent()
    {
        return false;
    }
};
}
}
}
