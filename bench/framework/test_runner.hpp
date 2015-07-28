#pragma once

#include <bench/core/clock.hpp>
#include <bench/core/test_instance.hpp>
#include <bench/framework/test_thread.hpp>
#include <utils/memory.hpp>

#include <chrono>
#include <iostream>

namespace bench
{
namespace framework
{
class test_runner
{
public:
    test_runner(test_instance & test) : _test(test)
    {
    }

    ~test_runner()
    {
    }

    void run()
    {
        create_threads();
        start_threads();
        collect_samples();
        stop_threads();
    }

private:
    void create_threads()
    {
        for (int i = 0; i < _test.config.thread_count; i++)
            _threads.emplace_back(utils::make_unique<test_thread>(_test));
    }

    void start_threads()
    {
        _test.start_time = clock::now();
        for (auto & thread : _threads)
            thread->start();
    }

    void stop_threads()
    {
        for (auto & thread : _threads)
            thread->stop();
    }

    void sample_now()
    {
        sample<unsigned long> sample;
        sample.time = clock::now();
        for (auto & thread : _threads)
        {
            sample.values.push_back(thread->iterations());
        }

        _test.result.emplace_back(sample);
    }

    void collect_samples()
    {
        const clock::duration sampling_period = std::chrono::milliseconds(100);
        clock::time_point stop_time = clock::now() + _test.config.duration;

        sample_now();

        while (clock::now() < stop_time)
        {
            std::this_thread::sleep_for(sampling_period);
            sample_now();
        }
    }

    test_instance & _test;
    std::vector<std::unique_ptr<test_thread>> _threads;
    clock::time_point _start_time;
};

void run_test(test_instance & test)
{
    test_runner(test).run();
}
}
}
