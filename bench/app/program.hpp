#pragma once

#include <bench/app/settings.hpp>
#include <bench/core/test_collection.hpp>
#include <bench/core/test_instance.hpp>
#include <bench/log/logger.hpp>

namespace bench
{
namespace app
{
class program
{
public:
    program(log::logger & logger, test_collection & pool) : _logger(logger), _test_pool(pool)
    {
    }

    void run(int argc, const char ** argv);

private:
    void parse_command_line(int argc, const char ** argv);
    void prepare_schedule();
    void run_scheduled_tests();
    void save_jsonp_report();
    bool should_run_test(std::string) const;

    settings _settings;
    log::logger & _logger;
    test_collection & _test_pool;
    std::vector<test_instance> _schedule;
};
}
}
