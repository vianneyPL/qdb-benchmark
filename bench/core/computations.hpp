#pragma once

#include <bench/core/test_instance.hpp>

namespace bench
{
double compute_average_speed(const test_instance &);
double compute_average_throughput(const test_instance &);
double compute_memory_variation(const test_instance &);
}
