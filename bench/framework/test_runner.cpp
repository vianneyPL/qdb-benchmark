#include <bench/core/clock.hpp>
#include <bench/core/test_instance.hpp>
#include <bench/core/probe.hpp>
#include <bench/framework/test_thread.hpp>
#include <bench/framework/test_iteration_probe.hpp>
#include <bench/log/logger.hpp>
#include <utils/memory.hpp>
#include <utils/for_each.hpp>

#include <chrono>
#include <iostream>

namespace bench
{
namespace framework
{
class test_runner
{
public:
    test_runner(test_instance & test, log::logger & logger) : _test(test), _logger(logger)
    {
        for (int i = 0; i < _test.config.thread_count; i++)
            _threads.emplace_back(new test_thread(_test));

        _probes = bench::create_test_probes(_test);
        _probes.emplace_back(new test_iteration_probe(_threads));
    }

    ~test_runner()
    {
    }

    void run()
    {
        if (step1_setup())
        {
            step2_test();
            step3_cleanup();
        }
    }

private:
    bool step1_setup()
    {
        _logger.setup_started(_test);
        auto start_time = clock::now();

        try
        {
            utils::for_each(_threads, &test_thread::setup);
            utils::for_each(_probes, &probe::setup);

            _test.setup_duration = clock::now() - start_time;

            _logger.setup_finished(_test);
            return true;
        }
        catch (std::exception & e)
        {
            _test.error = e.what();

            _logger.setup_failed(_test);
            return false;
        }
    }

    void step2_test()
    {
        _logger.test_started(_test);

        try
        {
            utils::for_each(_threads, &test_thread::run);
            _test.start_time = clock::now();

            sample_now();

            while (!timed_out())
            {
                wait();
                sample_now();
            }

            _test.test_duration = clock::now() - _test.start_time;
            _logger.test_finished(_test);
        }
        catch (std::exception & e)
        {
            _test.error = e.what();

            _logger.test_failed(_test);
        }
    }

    void step3_cleanup()
    {
        auto start_time = clock::now();
        _logger.cleanup_started(_test);

        try
        {
            utils::for_each(_threads, &test_thread::cleanup);
            utils::for_each(_probes, &probe::cleanup);

            _test.cleanup_duration = clock::now() - start_time;
            _logger.cleanup_finished(_test);
        }
        catch (std::exception & e)
        {
            _test.error = e.what();

            _logger.cleanup_failed(_test);
        }
    }

    bool timed_out()
    {
        return clock::now() > _test.start_time + _test.config.duration;
    }

    void wait()
    {
        const duration sampling_period = std::chrono::milliseconds(100);
        std::this_thread::sleep_for(sampling_period);
    }

    void sample_now()
    {
        time_point now = clock::now();

        for (auto & probe : _probes)
            probe->take_sample(now, _test.result);
    }

    test_instance & _test;
    test_thread_collection _threads;
    probe_collection _probes;
    log::logger & _logger;
};

void run_test(test_instance & test, log::logger & logger)
{
    test_runner(test, logger).run();
}
}
}
