#pragma once

#include <bench/core/test_instance.hpp>

#include <chrono>
#include <exception>
#include <thread>

namespace bench
{
namespace framework
{

using clock = std::chrono::high_resolution_clock;

class test_thread
{

public:
    struct sample_type
    {
        clock::time_point time;
        unsigned long iterations;
    };

    typedef std::vector<sample_type> resut_type;

    explicit test_thread(const test_instance & test)
        : _is_running(false), _eptr(nullptr), _iterations(0),
          _test_runner(create_test_runner(test)), _thread(&test_thread::run, this)
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

    const resut_type & result()
    {
        _thread.join();
        if (_eptr)
            std::rethrow_exception(_eptr);
        return _result;
    }

private:
    void run()
    {
        try
        {
            wait_to_start();

            while (_is_running)
            {
                run_single_iteration();

                if (is_time_to_save_sample())
                {
                    save_sample();
                }
            }
        }
        catch (...)
        {
            _eptr = std::current_exception();
        }
    }

    void wait_to_start() const
    {
        while (!_is_running)
            ;
    }

    void run_single_iteration()
    {

        _test_runner->run();
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

    const clock::duration _sampling_period = std::chrono::milliseconds(100);
    volatile bool _is_running;
    std::exception_ptr _eptr;
    resut_type _result;
    clock::time_point _next_sample_time;
    unsigned long _iterations;
    std::unique_ptr<test_runner> _test_runner;
    std::thread _thread;
};
}
}
