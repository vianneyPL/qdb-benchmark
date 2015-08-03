#pragma once

#include <bench/core/clock.hpp>
#include <bench/core/test_instance.hpp>
#include <bench/core/probe.hpp>
#include <bench/framework/test_thread.hpp>
#include <bench/framework/test_iteration_probe.hpp>
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
        create_probes(); // requires threads
        start_threads();
        collect_samples();
        stop_threads();
        save_result();
    }

private:
    void create_probes()
    {
        _probes = bench::create_test_probes(_test);
        _probes.emplace_back(new test_iteration_probe(_threads));
    }

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
        time_point now = clock::now();

        for (auto & probe : _probes)
            probe->take_sample(now);
    }

    void collect_samples()
    {
        const duration sampling_period = std::chrono::milliseconds(100);
        time_point stop_time = clock::now() + _test.config.duration;

        sample_now();

        while (clock::now() < stop_time)
        {
            std::this_thread::sleep_for(sampling_period);
            sample_now();
        }
    }

    void save_result()
    {
        for (auto & probe : _probes)
        {
            for (auto & pair : probe->result)
            {
                _test.result[pair.first] = pair.second;
            }
        }
    }

    test_instance & _test;
    test_thread_collection _threads;
    probe_collection _probes;
    time_point _start_time;
};

void run_test(test_instance & test)
{
    test_runner(test).run();
}
}
}
