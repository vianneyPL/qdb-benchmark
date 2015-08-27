#pragma once

#include <bench/core/clock.hpp>
#include <bench/core/test_instance.hpp>
#include <utils/master_slave_barrier.hpp>

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
    explicit test_thread(test_instance & test, utils::master_slave_barrier & barrier)
        : _test(test), _barrier(barrier), _thread(std::thread(&test_thread::main, this))
    {
    }

    ~test_thread()
    {
        if (_thread.joinable()) _thread.join();
    }

    unsigned long iterations() const
    {
        return _test_loop->iterations();
    }

    std::string setup_error() const
    {
        return _setup_error;
    }

    std::string test_error() const
    {
        return _test_error;
    }

    std::string cleanup_error() const
    {
        return _cleanup_error;
    }

private:
    void main()
    {
        wait();
        run_setup();
        notify();

        wait();
        run_test();
        notify();

        wait();
        run_cleanup();
        notify();
    }

    void run_setup()
    {
        try
        {
            _test_loop = create_test_loop(_test);
        }
        catch (std::exception & e)
        {
            _setup_error = e.what();
        }
    }

    void run_test()
    {
        if (!_test_loop) return;

        try
        {
            _test_loop->run();
        }
        catch (std::exception & e)
        {
            _test_error = e.what();
        }
    }

    void run_cleanup()
    {
        try
        {
            _test_loop.reset();
        }
        catch (std::exception & e)
        {
            _cleanup_error = e.what();
        }
    }

    void wait()
    {
        _barrier.wait_master();
    }

    void notify()
    {
        _barrier.notify_master();
    }

    test_instance & _test;
    std::string _setup_error, _test_error, _cleanup_error;
    utils::master_slave_barrier & _barrier;
    std::thread _thread;
    std::unique_ptr<test_loop> _test_loop;
};

class test_thread_collection : public std::vector<std::unique_ptr<test_thread>>
{
public:
    std::string first_setup_error() const
    {
        for (auto & t : *this)
            if (!t->setup_error().empty()) return t->setup_error();
        return "";
    }

    std::string first_test_error() const
    {
        for (auto & t : *this)
            if (!t->test_error().empty()) return t->test_error();
        return "";
    }

    std::string const first_cleanup_error()
    {
        for (auto & t : *this)
            if (!t->cleanup_error().empty()) return t->cleanup_error();
        return "";
    }
};
}
}
