#pragma once

#include <bench/tests/common/test_template.hpp>
#include <atomic>
#include <string>

namespace bench
{
namespace tests
{
namespace std_
{

class atomic : public test_template<atomic>
{
public:
    atomic(bench::test_config config) : test_template(config)
    {
    }

    void run_iteration(std::uint32_t iteration)
    {
        ++_value;
    }

    static std::string name()
    {
        return "std_atomic";
    }

    static std::string description()
    {
        return "Increment a shared std::atomic<std::uint32_t> by each thread.";
    }

    static bool size_dependent()
    {
        return false;
    }

private:
    // An atomic shared by all threads.
    static std::atomic<std::uint32_t> _value;
};

std::atomic<std::uint32_t> atomic::_value{0u};

} // namespace std_
} // namespace tests
} // namespace bench
