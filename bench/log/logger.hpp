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
    virtual void test_finished(int num, int total, const test_instance &) = 0;
    virtual void test_started(int num, int total, const test_instance &) = 0;
};

logger & get_logger();
}
}
