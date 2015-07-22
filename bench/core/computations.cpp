#include <bench/core/computations.hpp>

#include <algorithm>

double bench::compute_average_speed(const bench::test_instance & result)
{
    unsigned long iterations = 0;
    unsigned long duration = 0;

    for (auto & thread : result.result.threads)
    {
        iterations += thread.back().iterations;
        duration = std::max(duration, thread.back().time);
    }

    return iterations * 1000.0 / duration;
}

double bench::compute_average_throughput(const bench::test_instance & test)
{
    return compute_average_speed(test) * test.config.content_size;
}
