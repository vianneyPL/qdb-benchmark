#pragma once

#include <bench/core/test_instance.hpp>
#include <bench/framework/time_sampler.hpp>

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

    void run()
    {
        std::vector<std::future<time_series>> results;

        _is_running = true;

        for (int i=0; i<_test.config().thread_count; i++)
            results.emplace_back(std::async(&test_runner::run_async, this));

        wait_test_duration();

        _is_running = false;

        for (auto& result : results)
        {
            time_series results = result.get();
            _test.result.threads.emplace_back(results);

            std::cout << " - Average speed = " << results.average() << " it/s" << std::endl;
        }
    }

private:
    time_series run_async() const
    {
        time_series results;
        time_sampler sampler(results);

        while (_is_running)
        {
            _test.run();
            sampler.sample();
        }

        return results;
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