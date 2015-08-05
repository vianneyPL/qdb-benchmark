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
public:
    explicit test_thread(test_instance & test)
        : _is_running(false), _iterations(0), _test(create_test_code(test))
    {
    }

    ~test_thread()
    {
        if (_thread.joinable()) _thread.join();
    }

    void setup()
    {
        _test->setup();
        _thread = std::thread(&test_thread::main, this);
    }

    void run()
    {
        _is_running = true;
    }

    void cleanup()
    {
        _is_running = false;
        _thread.join();
        _test->cleanup();
    }

    unsigned long iterations() const
    {
        if (_eptr) std::rethrow_exception(_eptr);
        return _iterations;
    }

private:
    void main()
    {
        try
        {
            run_test_loop();
        }
        catch (...)
        {
            _eptr = std::current_exception();
        }
    }

    void run_test_loop()
    {
        wait_to_start();

        while (_is_running)
        {
            _test->run();
            _iterations++;
        }
    }

    void wait_to_start() const
    {
        while (!_is_running)
            ;
    }

    volatile bool _is_running;
    volatile unsigned long _iterations;
    std::unique_ptr<test_code> _test;
    std::thread _thread;
    std::exception_ptr _eptr;
};

using test_thread_collection = std::vector<std::unique_ptr<test_thread>>;
}
}
