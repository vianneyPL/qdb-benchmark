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
    counter_probe(const test_thread_collection & thread) : _threads(thread)
    {
    }

    void setup() override
    {
    }

    void take_sample(time_point now, result_type & result) override
    {
        sample sample;
        sample.time = now;
        for (auto & thread : _threads)
        {
            sample.values.push_back(thread->iterations());
        }
        result["iterations"].emplace_back(sample);
    }

    void cleanup() override
    {
    }

private:
    const test_thread_collection & _threads;
};
}
}
