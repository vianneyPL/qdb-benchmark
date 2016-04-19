#pragma once

#include <bench/core/test_instance.hpp>

namespace bench
{

double compute_average_frequency(const test_instance &);
double compute_average_throughput(const test_instance &);
std::int64_t compute_iteration_count(const test_instance &);

} // namespace bench
