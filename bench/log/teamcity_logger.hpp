#pragma once

#include <bench/log/logger.hpp>
#include <utils/teamcity.hpp>

namespace bench
{
namespace log
{
class teamcity_logger : public logger
{
public:
    void fatal_error(const std::string & message)
    {
        utils::teamcity::build_problem(message);
    }

    void pause(std::chrono::duration<int>) override
    {
    }

    void schedule(const std::vector<test_instance> &) override
    {
    }

    // Test setup
    void setup_started(const test_instance & test) override
    {
        utils::teamcity::test_started(make_test_name(test));
    }

    void setup_failed(const test_instance & test) override
    {
        utils::teamcity::test_failed(make_test_name(test), "Test set up failed", test.error);
        utils::teamcity::test_finished(make_test_name(test));
    }

    void setup_finished(const test_instance & test) override
    {
    }

    // Test

    void test_started(const test_instance & test)
    {
    }

    void test_failed(const test_instance & test)
    {
        utils::teamcity::test_failed(make_test_name(test), test.error);
        utils::teamcity::test_finished(make_test_name(test));
    }

    void test_finished(const test_instance & test)
    {
        std::string test_name = make_test_name(test);

        if (test.config.content_size)
        {
            utils::teamcity::build_statistic(test_name + ".throughput.average",
                                             compute_average_throughput(test));
        }

        utils::teamcity::build_statistic(test_name + ".frequency.average",
                                         compute_average_frequency(test));
    }

    // Test cleanup

    void cleanup_started(const test_instance & test) override
    {
    }

    void cleanup_failed(const test_instance & test) override
    {
        utils::teamcity::test_failed(make_test_name(test), "Test set up failed", test.error);
        utils::teamcity::test_finished(make_test_name(test));
    }

    void cleanup_finished(const test_instance & test) override
    {
        utils::teamcity::test_finished(make_test_name(test));
    }

private:
    static std::string make_size_string(size_t size)
    {
        if (size < 1024) return std::to_string(size) + "_B";
        size /= 1024;
        if (size < 1024) return std::to_string(size) + "_kB";
        size /= 1024;
        if (size < 1024) return std::to_string(size) + "_MB";
        size /= 1024;
        return std::to_string(size) + "_GB";
    }

    static std::string make_thread_string(int thread_count)
    {
        if (thread_count > 1)
            return std::to_string(thread_count) + "_threads";
        else
            return "1_thread";
    }

    static std::string make_test_name(const bench::test_instance & test)
    {
        std::string s;
        s = test.tclass.name + "." + make_thread_string(test.config.thread_count);
        if (test.tclass.size_dependent) s += "." + make_size_string(test.config.content_size);
        return s;
    }
};
}
}
