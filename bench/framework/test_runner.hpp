#pragma once

#include <bench/core/test_instance.hpp>
#include <bench/framework/chronometer.hpp>

#include <future>
#include <thread>
#include <chrono>
#include <iostream>

namespace bench {
namespace framework {

class test_runner
{
    using clock = std::chrono::steady_clock;
    test_instance& _test;
    const clock::duration _duration;
    volatile bool _is_running;
    std::vector<std::future<time_series>> _futures;

public:
    test_runner(test_instance& test)
        : _test(test), _duration(std::chrono::seconds(2))
    {
        _test.init();
    }

    ~test_runner()
    {
        _test.cleanup();
    }    

    void run(/*std::function<void(int)> progress*/)
    {
        start_threads();
        wait_test_duration();
        stop_threads();
        collect_results();
    }

private:
    void start_threads()
    {
        _is_running = true;

        for (int i=0; i<_test.config().thread_count; i++)
            _futures.emplace_back(std::async(&test_runner::run_async, this));
    }

    void stop_threads()
    {
        _is_running = false;
    }

    void collect_results()
    {
        for (auto& result : _futures)
        {
            time_series _futures = result.get();
            _test.result.threads.emplace_back(_futures);
        }
    }

    time_series run_async() const
    {
        chronometer chrono;

        chrono.start();
        while (_is_running)
        {
            _test.run();
            chrono.step();
        }
        chrono.stop();

        return chrono.data();
    }

    void wait_test_duration() const 
    {        
        clock::time_point start_time = clock::now();

        while (progress(start_time)<100)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << " - " << progress(start_time) << "%" << std::endl;
        }
    }

    double progress(clock::time_point start_time) const
    {
        return (clock::now() - start_time).count() * 100 / _duration.count();
    }
};

void run_test(test_instance& test)
{
    test_runner(test).run();
}

}}