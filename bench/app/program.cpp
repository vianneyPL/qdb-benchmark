#include <bench/app/program.hpp>
#include <bench/app/command_line.hpp>
#include <bench/framework/test_runner.hpp>
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
        for (auto thread_count : _settings.thread_counts)
        {
            config.thread_count = thread_count;
            if (test_class->size_dependent)
            {
                for (auto content_size : _settings.content_sizes)
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
    for (auto i = 0u; i < _schedule.size(); i++)
    {
        auto & test_instance = _schedule[i];

        _logger.test_started(i + 1u, _schedule.size(), test_instance);
        bench::framework::run_test(test_instance, _probe_pool);
        _logger.test_finished(i + 1u, _schedule.size(), test_instance);

        _logger.pause(_settings.pause);
        std::this_thread::sleep_for(_settings.pause);
    }
}

void bench::app::program::save_jsonp_report()
{
    bench::report::jsonp(_schedule).save();
}
