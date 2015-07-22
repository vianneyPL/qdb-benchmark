#pragma once

#include <bench/core/test_collection.hpp>

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
    test_collection tests;
    std::chrono::duration<int> pause;
    std::chrono::duration<int> duration;
};
}
}
