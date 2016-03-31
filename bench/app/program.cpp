#include <bench/app/program.hpp>
#include <bench/app/command_line.hpp>
#include <bench/framework/test_runner.hpp>
#include <bench/report/jsonp.hpp>

#include <algorithm>
#include <iostream>
#include <thread>

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
            config.content_size = 0;
            config.content_count = 0;
            if (test_class->size_dependent && test_class->count_dependent)
            {
                for (auto content_size : _settings.content_sizes)
                {
                    config.content_size = content_size;
                    for (auto content_count : _settings.content_counts)
                    {
                        config.content_count = content_count;
                        _schedule.emplace_back(create_test_instance(*test_class, config));
                    }
                }
            }
            else if (test_class->size_dependent)
            {
                for (auto content_size : _settings.content_sizes)
                {
                    config.content_size = content_size;
                    _schedule.emplace_back(create_test_instance(*test_class, config));
                }
            }
            else if (test_class->count_dependent)
            {
                for (auto content_count : _settings.content_counts)
                {
                    config.content_count = content_count;
                    _schedule.emplace_back(create_test_instance(*test_class, config));
                }
            }
            else
            {
                _schedule.emplace_back(create_test_instance(*test_class, config));
            }
        }
    }

    _logger.schedule(_schedule);
}

void bench::app::program::run_scheduled_tests()
{
    bench::framework::test_runner runner(_logger);
#if BENCHMARK_SNMP
    runner.set_snmp_peers(_settings.snmp_peers);
#endif

    for (auto & test : _schedule)
    {
        runner.run(test);
        _report.add_test(test);

        _logger.pause(_settings.pause);
        std::this_thread::sleep_for(_settings.pause);
    }
}
