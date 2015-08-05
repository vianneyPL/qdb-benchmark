#include <bench/log/console_logger.hpp>
#include <bench/log/teamcity_logger.hpp>

bench::log::logger & bench::log::get_teamcity_logger()
{
    static logger * instance = new teamcity_logger();
    return *instance;
}

bench::log::logger & bench::log::get_console_logger()
{
    static logger * instance = new console_logger();
    return *instance;
}