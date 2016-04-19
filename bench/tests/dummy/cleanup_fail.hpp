#pragma once

#include <bench/tests/common/test_template.hpp>

#include <thread>

namespace bench
{
namespace tests
{
namespace dummy
{
class cleanup_fail : public test_template<cleanup_fail>
{
public:
    cleanup_fail(bench::test_config config) : test_template(config)
    {
    }

    void run_iteration(std::uint32_t iteration)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    void cleanup() override
    {
        throw std::runtime_error("This exception has been intentionally thrown during cleanup.");
    }

    static std::string name()
    {
        return "dummy_cleanup_fail";
    }

    static std::string description()
    {
        return "Throws in cleanup";
    }

    static bool size_dependent()
    {
        return false;
    }
};
}
}
}
