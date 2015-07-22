#include <bench/log/teamcity_logger.hpp>
#include <bench/core/computations.hpp>

#include <iostream>
#include <sstream>

static std::string make_size_string(size_t size)
{
    if (size < 1024)
        return std::to_string(size) + "_B";
    size /= 1024;
    if (size < 1024)
        return std::to_string(size) + "_kB";
    size /= 1024;
    if (size < 1024)
        return std::to_string(size) + "_MB";
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
    s = test.tclass.id + "." + make_thread_string(test.config.thread_count);
    if (test.tclass.size_dependent)
        s += "." + make_size_string(test.config.content_size);
    return s;
}

void bench::log::teamcity_logger::fatal_error(const std::string & message)
{
    std::cout << "##teamcity[buildProblem description='" << message << "']" << std::endl;
}

void bench::log::teamcity_logger::schedule(const std::vector<test_instance> & tests)
{
}

void bench::log::teamcity_logger::test_started(int num, int total, const test_instance & test)
{
    std::cout << "##teamcity[testStarted name='" << make_test_name(test)
              << "' captureStandardOutput='true']" << std::endl;
}

void bench::log::teamcity_logger::test_finished(int num, int total, const test_instance & test)
{
    std::cout << "##teamcity[testFinished name='" << make_test_name(test) << "']" << std::endl;
    std::cout << "##teamcity[buildStatisticValue key='" << make_test_name(test)
              << ".throughput.average' value='" << compute_average_throughput(test) << "']"
              << std::endl;
}
