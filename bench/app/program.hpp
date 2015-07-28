#pragma once

#include <bench/app/settings.hpp>
#include <bench/core/test_collection.hpp>
#include <bench/core/test_instance.hpp>
#include <bench/core/probe_class.hpp>
#include <bench/framework/probe_thread.hpp>
#include <bench/log/logger.hpp>

namespace bench
{
namespace app
{
class program
{
public:
    program(log::logger & logger, test_collection & test_pool, probe_collection & probe_pool)
        : _logger(logger), _test_pool(test_pool), _probe_pool(probe_pool)
    {
    }

    void run(int argc, const char ** argv)
    {
        parse_command_line(argc, argv);
        prepare_schedule();
        start_probe_thread();
        run_scheduled_tests();
        stop_probe_thread();
        save_jsonp_report();
    }

private:
    void parse_command_line(int argc, const char ** argv);
    void prepare_schedule();
    void run_scheduled_tests();
    void start_probe_thread();
    void stop_probe_thread();
    void save_jsonp_report();

    settings _settings;
    log::logger & _logger;
    test_collection & _test_pool;
    probe_collection & _probe_pool;
    std::vector<test_instance> _schedule;
    std::vector<probe_instance> _probes;
    framework::probe_thread _probe_thread;
};
}
}
