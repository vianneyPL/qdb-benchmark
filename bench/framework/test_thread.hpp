#pragma once

#include <bench/core/clock.hpp>
#include <bench/core/test_instance.hpp>

#include <chrono>
#include <exception>
#include <thread>

namespace bench
{
namespace framework
{
class test_thread
{
    using result_type = std::vector<unsigned long>;

public:
    explicit test_thread(const test_instance & test)
        : _is_running(false), _iterations(0), _eptr(nullptr), _test_code(create_test_code(test)),
          _thread(&test_thread::run, this)
    {
    }

    void start()
    {
        _is_running = true;
    }

    void stop()
    {
        _is_running = false;
        _thread.join();
        if (_eptr)
            std::rethrow_exception(_eptr);
    }

    unsigned long iterations()
    {
        return _iterations;
    }

private:
    void run()
    {
        wait_to_start();
        try
        {
            while (_is_running)
                run_single_iteration();
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
        _test_code->run();
        _iterations++;
    }

    volatile bool _is_running;
    volatile unsigned long _iterations;
    std::exception_ptr _eptr;
    std::unique_ptr<test_code> _test_code;
    std::thread _thread;
};
}
}
