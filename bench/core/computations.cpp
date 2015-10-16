#include <bench/core/computations.hpp>

#include <algorithm>
#include <numeric>

static double sum_values(const bench::sample & sample)
{
    return (double)std::accumulate(sample.values.begin(), sample.values.end(), std::int64_t());
}

double bench::compute_average_frequency(const bench::test_instance & test)
{
    const sample & last_sample = test.result.at("iterations").back();

    auto iterations = sum_values(last_sample);

    time_point stop_time = last_sample.time;
    duration elapsed = stop_time - test.start_time;
    auto elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

    return 1000.0 * iterations / elapsed_millis;
}

double bench::compute_average_throughput(const bench::test_instance & test)
{
    return compute_average_frequency(test) * test.config.content_size;
}

double bench::compute_iteration_count(const bench::test_instance & test)
{
    auto & serie = test.result.at("iterations");
    return (double)sum_values(serie.back());
}
