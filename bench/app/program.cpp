#include <bench/app/program.hpp>
#include <bench/app/command_line.hpp>
#include <bench/framework/test_runner.hpp>
#include <bench/report/jsonp.hpp>

#include <algorithm>
#include <iostream>

void bench::app::program::run(int argc, const char ** argv)
{
    parse_command_line(argc, argv);
    prepare_schedule();
    run_scheduled_tests();
    save_jsonp_report();
}

void bench::app::program::parse_command_line(int argc, const char ** argv)
{
    command_line parser(_test_pool, _settings);
    parser.parse(argc, argv);
}

bool bench::app::program::should_run_test(std::string id) const
{
    if (_settings.tests.empty())
        return true;

    return std::find(_settings.tests.begin(), _settings.tests.end(), id) != _settings.tests.end();
}

void bench::app::program::prepare_schedule()
{
    test_config config;
    config.cluster_uri = _settings.cluster_uri;
    config.duration = _settings.duration;

    for (auto & test_class : _test_pool)
    {
        if (!should_run_test(test_class->id))
            continue;

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

        std::this_thread::sleep_for(_settings.pause);
    }
}

void bench::app::program::save_jsonp_report()
{
    bench::report::jsonp report;
    for (auto & test : _schedule)
    {
        report.add_test(test);
    }
    report.save();
}
