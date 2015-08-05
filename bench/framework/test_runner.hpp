#pragma once

#include <bench/core/test_instance.hpp>
#include <bench/log/logger.hpp>

namespace bench
{
namespace framework
{
void run_test(test_instance &, log::logger &);
}
}
