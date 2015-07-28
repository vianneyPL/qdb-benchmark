#include <bench/app/program.hpp>
#include <bench/app/command_line.hpp>
#include <bench/framework/test_runner.hpp>
#include <bench/framework/probe_sampler.hpp>
#include <bench/report/jsonp.hpp>

#include <algorithm>
#include <iostream>

void bench::app::program::parse_command_line(int argc, const char ** argv)
{
    command_line parser(_test_pool, _settings);
    parser.parse(argc, argv);
}

void bench::app::program::prepare_schedule()
{
    test_config config;
    config.cluster_uri = _settings.cluster_uri;
    config.duration = _settings.duration;

    for (auto & test_class : _settings.tests)
    {
        for (int thread_count : _settings.thread_counts)
        {
            config.thread_count = thread_count;
            if (test_class->size_dependent)
            {
                for (int content_size : _settings.content_sizes)
                {
                    config.content_size = content_size;
                    _schedule.emplace_back(create_test_instance(*test_class, config));
                }
            }
            else
            {
                config.content_size = 0;
                _schedule.emplace_back(create_test_instance(*test_class, config));
            }
        }
    }

    _logger.schedule(_schedule);
}

void bench::app::program::run_scheduled_tests()
{
    for (unsigned i = 0; i < _schedule.size(); i++)
    {
        auto & test_instance = _schedule[i];

        _logger.test_started(i + 1, _schedule.size(), test_instance);
        bench::framework::run_test(test_instance);
        _logger.test_finished(i + 1, _schedule.size(), test_instance);

        _logger.pause(_settings.pause);
        std::this_thread::sleep_for(_settings.pause);
    }
}

void bench::app::program::start_probe_thread()
{
    probe_config cfg;
    cfg.node_uri = _settings.cluster_uri; // :-(
    for (auto probe : _probe_pool)
    {
        _probes.emplace_back(create_probe_instance(*probe, cfg));
    }
    _probe_thread.start(_probes);
}

void bench::app::program::stop_probe_thread()
{
    _probe_thread.stop();
}

void bench::app::program::save_jsonp_report()
{
    bench::report::jsonp(_schedule, _probes).save();
}
