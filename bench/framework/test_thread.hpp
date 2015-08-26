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
    explicit test_thread(test_instance & test) : _is_running(false), _test(test)
    {
    }

    ~test_thread()
    {
        if (_thread.joinable()) _thread.join();
    }

    void setup()
    {
        _test_loop = create_test_loop(_test);
        _thread = std::thread(&test_thread::main, this);
    }

    void run()
    {
        _is_running = true;
    }

    void cleanup()
    {
        _thread.join();
        _test_loop.reset();
    }

    unsigned long iterations() const
    {
        if (_eptr) std::rethrow_exception(_eptr);
        return _test_loop->iterations();
    }

    bool is_running() const
    {
        return _is_running;
    }

private:
    void main()
    {
        wait_to_start();

        try
        {
            _test_loop->run(clock::now() + _test.config.duration);
        }
        catch (...)
        {
            _eptr = std::current_exception();
        }

        _is_running = false;
    }

    void wait_to_start() const
    {
        while (!_is_running)
            ;
    }

    volatile bool _is_running;
    test_instance & _test;
    std::unique_ptr<test_loop> _test_loop;
    std::thread _thread;
    std::exception_ptr _eptr;
};

using test_thread_collection = std::vector<std::unique_ptr<test_thread>>;
}
}
