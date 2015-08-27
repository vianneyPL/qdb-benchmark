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
#include <algorithm>

namespace bench
{
namespace framework
{
class test_runner
{
public:
    test_runner(test_instance & test, log::logger & logger)
        : _test(test), _logger(logger), _barrier(_test.config.thread_count)
    {
        for (int i = 0; i < _test.config.thread_count; i++)
            _threads.emplace_back(new test_thread(_test, _barrier));

        _probes = bench::create_test_probes(_test);
        _probes.emplace_back(new test_iteration_probe(_threads));
    }

    ~test_runner()
    {
    }

    void run()
    {
        step1_setup();
        step2_test();
        step3_cleanup();
    }

private:
    void step1_setup()
    {
        _logger.setup_started(_test);
        auto start_time = clock::now();

        _barrier.notify_slaves();

        setup_probes();

        _barrier.wait_slaves();

        _test.setup_duration = clock::now() - start_time;

        set_setup_error(_threads.first_setup_error());

        if (_setup_error.empty())
            _logger.setup_finished(_test);
        else
            _logger.setup_failed(_test, _setup_error);
    }

    void setup_probes()
    {
        try
        {
            utils::for_each(_probes, &probe::setup);
        }
        catch (std::exception & e)
        {
            set_setup_error(e.what());
        }
    }

    void step2_test()
    {
        if (!_test.error.empty())
        {
            _barrier.notify_slaves();
            _barrier.wait_slaves();
            return;
        }

        const duration sampling_period = std::chrono::milliseconds(100);

        _logger.test_started(_test);
        _test.start_time = clock::now();

        _barrier.notify_slaves();
        sample_now();
        while (!_barrier.wait_slaves_for(sampling_period))
        {
            sample_now();
        }
        sample_now();

        _test.test_duration = clock::now() - _test.start_time;

        set_test_error(_threads.first_test_error());

        if (_test_error.empty())
            _logger.test_finished(_test);
        else
            _logger.test_failed(_test, _test_error);
    }

    void step3_cleanup()
    {
        _logger.cleanup_started(_test);
        auto start_time = clock::now();

        _barrier.notify_slaves();
        cleanup_probes();
        _barrier.wait_slaves();
        _test.cleanup_duration = clock::now() - start_time;

        set_cleanup_error(_threads.first_cleanup_error());

        if (_cleanup_error.empty())
            _logger.cleanup_finished(_test);
        else
            _logger.cleanup_failed(_test, _cleanup_error);
    }

    void cleanup_probes()
    {
        try
        {
            utils::for_each(_probes, &probe::cleanup);
        }
        catch (std::exception & e)
        {
            set_cleanup_error(e.what());
        }
    }

    void sample_now()
    {
        time_point now = clock::now();

        for (auto & probe : _probes)
            probe->take_sample(now, _test.result);
    }

    void set_setup_error(std::string err)
    {
        if (err.empty()) return;
        if (_setup_error.empty()) _setup_error = err;
        if (_test.error.empty()) _test.error = "Setup error: " + err;
    }

    void set_test_error(std::string err)
    {
        if (err.empty()) return;
        if (_test_error.empty()) _test_error = err;
        if (_test.error.empty()) _test.error = err;
    }

    void set_cleanup_error(std::string err)
    {
        if (err.empty()) return;
        if (_cleanup_error.empty()) _cleanup_error = err;
        if (_test.error.empty()) _test.error = "Cleanup error: " + err;
    }

    test_instance & _test;
    test_thread_collection _threads;
    probe_collection _probes;
    log::logger & _logger;
    utils::master_slave_barrier _barrier;
    std::string _setup_error, _test_error, _cleanup_error;
};

void run_test(test_instance & test, log::logger & logger)
{
    test_runner(test, logger).run();
}
}
}
