#include <bench/core/clock.hpp>
#include <bench/core/test_instance.hpp>
#include <bench/core/probe.hpp>
#include <bench/framework/test_thread.hpp>
#include <bench/framework/test_iteration_probe.hpp>
#include <bench/log/logger.hpp>
#include <utils/memory.hpp>
#include <utils/for_each.hpp>

#include <chrono>
#include <algorithm>

namespace bench
{
namespace framework
{
duration compute_sampling_period(duration test_duration)
{
    const duration longest = std::chrono::minutes(1);
    const duration shortest = std::chrono::milliseconds(100);
    return std::min(std::max(shortest, test_duration / 100), longest);
}

class test_runner
{
public:
    test_runner(test_instance & test, log::logger & logger)
        : _test(test), _logger(logger), _synchronizer(_test.config.thread_count)
    {
        for (int i = 0; i < _test.config.thread_count; i++)
            _threads.emplace_back(new test_thread(_test, _synchronizer));
        _synchronizer.wait_workers();

        _probes = bench::create_test_probes(_test);
        _probes.emplace_back(new test_iteration_probe(_threads));

        _sampling_period = compute_sampling_period(_test.config.duration);
    }

    ~test_runner()
    {
        _synchronizer.send_order(&test_thread::terminate);
    }

    void run()
    {
        if (step1_setup())
        {
            step2_test();
        }
        step3_cleanup();
    }

private:
    bool step1_setup()
    {
        try
        {
            auto start_time = clock::now();
            _logger.setup_started(_test);

            _synchronizer.send_order(&test_thread::setup);
            setup_probes();
            _synchronizer.wait_workers();
            _test.setup_duration = clock::now() - start_time;

            _synchronizer.rethrow();

            _logger.setup_finished(_test);
            return true;
        }
        catch (std::exception & e)
        {
            _test.error = std::string("Setup error: ") + e.what();
            _logger.setup_failed(_test, e.what());
            return false;
        }
    }

    void step2_test()
    {
        try
        {
            _test.start_time = clock::now();
            _logger.test_started(_test);

            _synchronizer.send_order(&test_thread::test);
            sample_now();
            while (!_synchronizer.wait_workers_for(_sampling_period))
            {
                sample_now();
            }
            sample_now();
            _test.test_duration = clock::now() - _test.start_time;

            _synchronizer.rethrow();

            _logger.test_finished(_test);
        }
        catch (std::exception & e)
        {
            _test.error = e.what();
            _logger.test_failed(_test, e.what());
        }
    }

    void step3_cleanup()
    {
        try
        {
            auto start_time = clock::now();
            _logger.cleanup_started(_test);

            _synchronizer.send_order(&test_thread::cleanup);
            cleanup_probes();
            _synchronizer.wait_workers();

            _test.cleanup_duration = clock::now() - start_time;

            _synchronizer.rethrow();

            _logger.cleanup_finished(_test);
        }
        catch (std::exception & e)
        {
            _test.error = std::string("Cleanup error: ") + e.what();
            _logger.cleanup_failed(_test, e.what());
        }
    }

    void setup_probes()
    {
        for (auto & probe : _probes)
        {
            try
            {
                probe->setup();
            }
            catch (...)
            {
                _synchronizer.report_exception(std::current_exception());
            }
        }
    }

    void cleanup_probes()
    {
        for (auto & probe : _probes)
        {
            try
            {
                probe->cleanup();
            }
            catch (...)
            {
                _synchronizer.report_exception(std::current_exception());
            }
        }
    }

    void sample_now()
    {
        time_point now = clock::now();

        for (auto & probe : _probes)
        {
            try
            {
                probe->take_sample(now, _test.result);
            }
            catch (...)
            {
                _synchronizer.report_exception(std::current_exception());
            }
        }
    }

    test_instance & _test;
    log::logger & _logger;
    thread_synchronizer<test_thread> _synchronizer;
    test_thread_collection _threads;
    probe_collection _probes;
    duration _sampling_period;
};

void run_test(test_instance & test, log::logger & logger)
{
    test_runner(test, logger).run();
}
}
}
