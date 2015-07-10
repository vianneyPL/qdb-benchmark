#pragma once

#include <bench/core/test_instance.hpp>

#include <future>
#include <thread>
#include <chrono>

namespace bench {
namespace framework {

class test_runner
{
    test_instance& _test;

public:
    test_runner(test_instance& test)
        : _test(test)
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

        for (int i=0; i<_test.config().thread_count; i++)
            results.emplace_back(std::async(&test_runner::run_async, this));

        for (auto& result : results)
            _test.result.threads.emplace_back(result.get());
    }

private:
    time_series run_async() const
    {
        time_series ts;
        _test.run();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return ts;
    }
};

void run_test(test_instance& test)
{
    test_runner(test).run();
}

}}