#pragma once

#include <bench/core/test_instance.hpp>

#include <thread>
#include <chrono>

namespace bench {
namespace framework {

using clock = std::chrono::high_resolution_clock;

class test_thread {

public:
    struct sample_type {
        clock::time_point time;
        unsigned long iterations;
    }; 

    typedef std::vector<sample_type> resut_type;

    explicit test_thread(const test_instance& test)
        : _test(test), _is_running(false), _thread(&test_thread::run, this), _iterations(0)
    {
    }

    void start()
    {        
        _is_running = true;
    }

    void stop()
    {
        _is_running = false;       
    }

    const resut_type& result()
    { 
        _thread.join();
        return _result;
    }

private:
    void run()
    {
        wait_to_start();
        save_sample();
        
        while (_is_running)
        {
            run_single_iteration();

            if (is_time_to_save_sample())
            {
                save_sample();
            }
        }

        save_sample();
    }

    void wait_to_start() const
    {
        while(!_is_running);
    }

    void run_single_iteration()
    {
        _test.run();
        _iterations++;
    }

    bool is_time_to_save_sample() const
    {
        return clock::now() >= _next_sample_time;
    }

    void save_sample()
    {
         _result.push_back({clock::now(), _iterations});
         _next_sample_time = clock::now() + _sampling_period;
    }

    const test_instance& _test;
    const clock::duration _sampling_period = std::chrono::milliseconds(100);
    volatile bool _is_running;
    std::thread _thread;
    resut_type _result;
    clock::time_point _next_sample_time;
    unsigned long _iterations;
};
}}