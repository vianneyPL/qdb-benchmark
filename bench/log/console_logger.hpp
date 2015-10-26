#pragma once

#include <bench/log/logger.hpp>
#include <bench/log/unit.hpp>
#include <bench/core/computations.hpp>

#include <chrono>
#include <iostream>

namespace bench
{
namespace log
{
class console_logger : public logger
{
public:
    void fatal_error(const std::string & message) override
    {
        std::cerr << "ERROR: " << message << std::endl;
    }

    void pause(std::chrono::duration<int> duration) override
    {
        std::cout << std::endl << "Wait " << duration_to_string(duration) << std::endl << std::endl;
    }

    void schedule(const std::vector<test_instance> & tests) override
    {
        std::cout << "The following test will be performed: " << std::endl;
        for (unsigned i = 0; i < tests.size(); i++)
        {
            auto & test = tests[i];
            std::cout << "  " << (i + 1) << ". " << test.tclass.name;
            std::cout << ", threads=" << test.config.thread_count;
            if (test.tclass.size_dependent) std::cout << ", size=" << test.config.content_size;
            std::cout << std::endl;
        }
        std::cout << std::endl;

        _test_count = tests.size();
        _test_num = 0;
    }

    // Test setup

    void setup_started(const test_instance & test) override
    {
        _test_num++;

        std::cout << "Now running test " << _test_num << "/" << _test_count << ":" << std::endl;
        std::cout << "  - test = " << test.tclass.name << " (" << test.tclass.description << ")"
                  << std::endl;
        std::cout << "  - thread count = " << test.config.thread_count << std::endl;
        if (test.tclass.size_dependent)
            std::cout << "  - content size = "
                      << unit::byte(static_cast<double>(test.config.content_size)) << std::endl;

        std::cout << "Setting up test... " << std::endl;
    }

    void setup_failed(const test_instance & test, const std::string & error) override
    {
        std::cout << "Setting up test... FAILED (" << error << ")" << std::endl;
    }

    void setup_finished(const test_instance & test) override
    {
        std::cout << "Setting up test... OK (" << duration_to_string(test.setup_duration) << ")"
                  << std::endl;
    }

    // Test

    void test_started(const test_instance & test) override
    {
        std::cout << "Executing test... " << std::flush;
    }

    void test_progress(const test_instance & test) override
    {
        auto elapsed = clock::now() - test.start_time;
        auto iterations = compute_iteration_count(test);
        std::cout << "\rExecuting test... " << unit::none(iterations) << "iterations ("
                  << duration_to_string(elapsed) << ")      " << std::flush;
    }

    void test_failed(const test_instance & test, const std::string & error) override
    {
        std::cout << "\nExecuting test... FAILED (" << error << ")" << std::endl;
        std::cout << "  - total iterations = " << unit::none(compute_iteration_count(test))
                  << std::endl;
    }

    void test_finished(const test_instance & test) override
    {
        std::cout << "\nExecuting test... OK (" << duration_to_string(test.test_duration) << ")"
                  << std::endl;

        if (test.tclass.size_dependent)
        {
            std::cout << "  - average throughput = "
                      << unit::byte_per_second(compute_average_throughput(test)) << std::endl;
        }

        std::cout << "  - average frequency = " << unit::hertz(compute_average_frequency(test))
                  << std::endl;

        std::cout << "  - total iterations = " << unit::none(compute_iteration_count(test))
                  << std::endl;
    }

    // Test cleanup

    void cleanup_started(const test_instance & test) override
    {
        std::cout << "Cleaning up... " << std::endl;
    }

    void cleanup_failed(const test_instance & test, const std::string & error) override
    {
        std::cout << "Cleaning up... FAILED (" << error << ")" << std::endl;
    }

    void cleanup_finished(const test_instance & test) override
    {
        std::cout << "Cleaning up... OK (" << duration_to_string(test.cleanup_duration) << ")"
                  << std::endl;
    }

private:
    size_t _test_count;
    size_t _test_num;

    std::string duration_to_string(duration duration)
    {
        return unit::milliseconds(
            (double)std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
    }
};
}
}
