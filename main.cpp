#include <bench/app/program.hpp>
#include <bench/log/console_logger.hpp>
#include <bench/log/teamcity_logger.hpp>
#include <bench/tests/all_tests.hpp>

#include <cstdlib>
#include <iostream>

static bench::log::logger & get_logger()
{
    if (std::getenv("TEAMCITY_VERSION"))
        return *new bench::log::teamcity_logger();
    else
        return *new bench::log::console_logger();
}

int main(int argc, const char * argv[])
{
    bench::log::logger & logger = get_logger();
    bench::test_collection test_pool = bench::tests::get_all_tests();
    bench::app::program program(logger, test_pool);

    try
    {
        program.run(argc, argv);
        return EXIT_SUCCESS;
    }
    catch (std::exception & e)
    {
        logger.fatal_error(e.what());
        return EXIT_FAILURE;
    }
}
