#pragma once

#include <bench/core/test_instance.hpp>

#include <chrono>

namespace bench
{
namespace log
{
class logger
{
public:
    virtual void fatal_error(const std::string & message) = 0;
    virtual void pause(std::chrono::duration<int>) = 0;
    virtual void schedule(const std::vector<test_instance> &) = 0;

    virtual void setup_started(const test_instance &) = 0;
    virtual void setup_failed(const test_instance &) = 0;
    virtual void setup_finished(const test_instance &) = 0;

    virtual void test_started(const test_instance &) = 0;
    virtual void test_progress(const test_instance &) = 0;
    virtual void test_failed(const test_instance &) = 0;
    virtual void test_finished(const test_instance &) = 0;

    virtual void cleanup_started(const test_instance &) = 0;
    virtual void cleanup_failed(const test_instance &) = 0;
    virtual void cleanup_finished(const test_instance &) = 0;
};

logger & get_teamcity_logger();
logger & get_console_logger();
}
}
