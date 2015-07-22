#pragma once

#include <bench/log/logger.hpp>

namespace bench
{
namespace log
{
class console_logger : public logger
{
public:
    void fatal_error(const std::string & message) override;

    void schedule(const std::vector<test_instance> & tests) override;

    void test_started(int num, int total, const test_instance & test) override;

    void test_finished(int num, int total, const test_instance &) override;
};
}
}
