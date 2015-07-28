#pragma once

#include <bench/framework/probe_sampler.hpp>
#include <utils/memory.hpp>

#include <chrono>
#include <thread>
#include <iostream>

namespace bench
{
namespace framework
{
class probe_thread
{
public:
    void start(std::vector<probe_instance> & probes)
    {
        for (auto & probe : probes)
        {
            _probes.push_back(&probe);
        }

        _running = true;
        _thread = utils::make_unique<std::thread>(&probe_thread::run, this);
    }

    void stop()
    {
        _running = false;
        _thread->join();
    }

private:
    void run()
    {
        std::vector<probe_sampler> samplers;
        for (auto & probe : _probes)
            samplers.emplace_back(*probe);

        while (_running)
        {
            for (auto & sampler : samplers)
                sampler.save_sample();
            wait();
        }
    }

    void wait() const
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    volatile bool _running;
    clock::time_point _start_time;
    std::unique_ptr<std::thread> _thread;
    std::vector<probe_instance *> _probes;
};
}
}
