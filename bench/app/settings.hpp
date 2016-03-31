#pragma once

#include <bench/core/test_class.hpp>

#include <chrono>
#include <string>
#include <vector>

namespace bench
{
namespace app
{
struct settings
{
    std::string cluster_uri;
    std::vector<int> thread_counts;
    std::vector<std::size_t> content_sizes;
    std::vector<std::size_t> content_counts;
    test_class_collection tests;
    std::chrono::duration<int> pause;
    std::chrono::duration<int> duration;

#if BENCHMARK_SNMP
    std::vector<std::string> snmp_peers;
#endif
};
}
}
