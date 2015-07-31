#pragma once

#include <bench/app/settings.hpp>
#include <bench/core/test_class.hpp>
#include <bench/core/test_instance.hpp>
#include <bench/core/probe_class.hpp>
#include <bench/log/logger.hpp>

namespace bench
{
namespace app
{
class program
{
public:
    program(log::logger & logger,
            test_class_collection & test_pool,
            probe_class_collection & probe_pool)
        : _logger(logger), _test_pool(test_pool), _probe_pool(probe_pool)
    {
    }

    void run(int argc, const char ** argv)
    {
        parse_command_line(argc, argv);
        prepare_schedule();
        run_scheduled_tests();
        save_jsonp_report();
    }

private:
    void parse_command_line(int argc, const char ** argv);
    void prepare_schedule();
    void run_scheduled_tests();
    void save_jsonp_report();

    settings _settings;
    log::logger & _logger;
    test_class_collection & _test_pool;
    probe_class_collection & _probe_pool;
    test_instance_collection _schedule;
};
}
}
