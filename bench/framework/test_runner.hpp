#pragma once

#include <bench/core/clock.hpp>
#include <bench/core/test_instance.hpp>
#include <bench/core/probe_instance.hpp>
#include <bench/core/probe_class.hpp>
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
    test_runner(test_instance & test, const probe_class_collection & probe_pool)
        : _test(test), _probe_pool(probe_pool)
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
        probe_config cfg;
        cfg.node_uri = _test.config.cluster_uri; // :-(
        for (auto probe_class : _probe_pool)
        {
            _probes.push_back(probe_class->create_instance(cfg));
        }
        //_probes.push_back(utils::make_unique<test_iteration_probe>(_threads));
        _probes.push_back(std::unique_ptr<probe_instance>(new test_iteration_probe(_threads)));
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
    probe_instance_collection _probes;
    probe_class_collection _probe_pool;
    time_point _start_time;
};

void run_test(test_instance & test, const probe_class_collection & probes)
{
    test_runner(test, probes).run();
}
}
}
