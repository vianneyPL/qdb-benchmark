#include <bench/core/computations.hpp>

#include <algorithm>
#include <numeric>

double bench::compute_average_speed(const bench::test_instance & test)
{
    const sample<unsigned long> & last_sample = test.result.back();
    unsigned long iterations =
        std::accumulate(last_sample.values.begin(), last_sample.values.end(), 0);
    clock::time_point stop_time = last_sample.time;

    clock::duration duration = stop_time - test.start_time;
    return (double)iterations / std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

double bench::compute_average_throughput(const bench::test_instance & test)
{
    return compute_average_speed(test) * test.config.content_size;
}
