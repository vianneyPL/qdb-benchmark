#pragma once

#include <bench/framework/test_thread.hpp>
#include <bench/core/probe_instance.hpp>

namespace bench
{
namespace framework
{
class test_iteration_probe : public probe_instance
{
public:
    test_iteration_probe(const test_thread_collection & thread) : _threads(thread)
    {
    }

    void take_sample(time_point now) override
    {
        sample sample;
        sample.time = now;
        for (auto & thread : _threads)
        {
            sample.values.push_back(thread->iterations());
        }
        result["iterations"].emplace_back(sample);
    }

private:
    const test_thread_collection & _threads;
};
}
}
