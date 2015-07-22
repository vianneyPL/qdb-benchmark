#include <bench/log/console_logger.hpp>

#include <iostream>

void bench::log::console_logger::fatal_error(const std::string & message)
{
    std::cerr << "ERROR: " << message << std::endl;
}

void bench::log::console_logger::schedule(const std::vector<test_instance> & tests)
{
    std::cout << "The following test will be performed: " << std::endl;
    for (unsigned i = 0; i < tests.size(); i++)
    {
        auto & test = tests[i];
        std::cout << "  " << (i + 1) << ". " << test.tclass.id;
        std::cout << ", threads=" << test.config.thread_count;
        if (test.tclass.size_dependent)
            std::cout << ", size=" << test.config.content_size;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void bench::log::console_logger::test_started(int num, int total, const test_instance & test)
{
    std::cout << "Now running test " << num << "/" << total << ":" << std::endl;
    std::cout << "  - test = " << test.tclass.id << " (" << test.tclass.description << ")"
              << std::endl;
    std::cout << "  - thread count = " << test.config.thread_count << std::endl;
    if (test.tclass.size_dependent)
        std::cout << "  - content size = " << test.config.content_size << std::endl;
}

void bench::log::console_logger::test_finished(int num, int total, const test_instance &)
{
    std::cout << "Done." << std::endl
              << std::endl;
}
