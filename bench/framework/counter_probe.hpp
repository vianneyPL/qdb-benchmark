#pragma once

#include <bench/framework/test_thread.hpp>
#include <bench/core/probe.hpp>

namespace bench
{
namespace framework
{
class counter_probe : public probe
{
public:
    counter_probe(const test_thread_collection & threads) : _threads(threads)
    {
        define_measurement("test.iterations", "Test Loop Iterations", unit::none, threads.size());
    }

    void setup() override
    {
    }

    void take_sample() override
    {
        for (std::size_t i = 0; i < _threads.size(); i++)
            set_measured_value("test.iterations", i, _threads[i]->iterations());
    }

    void cleanup() override
    {
    }

private:
    const test_thread_collection & _threads;
};
}
}
