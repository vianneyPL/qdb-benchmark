#include <bench/log/console_logger.hpp>
#include <bench/core/computations.hpp>

#include <iostream>

static std::string make_size_string(size_t value)
{
    if (value < 1024)
        return std::to_string(value) + " B";
    value /= 1024;
    if (value < 1024)
        return std::to_string(value) + " kB";
    value /= 1024;
    if (value < 1024)
        return std::to_string(value) + " MB";
    value /= 1024;
    return std::to_string(value) + " GB";
}

static std::string make_speed_string(size_t value)
{
    if (value < 1000)
        return std::to_string(value) + " Hz";
    value /= 1000;
    if (value < 1000)
        return std::to_string(value) + " kHz";
    value /= 1000;
    if (value < 1000)
        return std::to_string(value) + " MHz";
    value /= 1000;
    return std::to_string(value) + " GHz";
}

void bench::log::console_logger::fatal_error(const std::string & message)
{
    std::cerr << "ERROR: " << message << std::endl;
}

void bench::log::console_logger::pause(std::chrono::duration<int> duration)
{
    std::cout << "Wait " << std::chrono::duration_cast<std::chrono::seconds>(duration).count()
              << " seconds";
    std::cout << std::endl
              << std::endl;
}

void bench::log::console_logger::schedule(const std::vector<test_instance> & tests)
{
    std::cout << "The following test will be performed: " << std::endl;
    for (unsigned i = 0; i < tests.size(); i++)
    {
        auto & test = tests[i];
        std::cout << "  " << (i + 1) << ". " << test.tclass.name;
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
    std::cout << "  - test = " << test.tclass.name << " (" << test.tclass.description << ")"
              << std::endl;
    std::cout << "  - thread count = " << test.config.thread_count << std::endl;
    if (test.tclass.size_dependent)
        std::cout << "  - content size = " << make_size_string(test.config.content_size)
                  << std::endl;
}

void bench::log::console_logger::test_finished(int num, int total, const test_instance & test)
{
    if (test.tclass.size_dependent)
    {
        std::cout << "Average throughput = "
                  << make_size_string((size_t)compute_average_throughput(test)) << "/s";
    }
    else
    {
        std::cout << "Average speed = " << make_speed_string((size_t)compute_average_speed(test));
    }

    std::cout << std::endl
              << std::endl;
}
