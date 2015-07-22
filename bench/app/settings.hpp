#pragma once

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
    std::vector<std::string> tests;
    std::chrono::duration<int> pause;
    std::chrono::duration<int> duration;
};
}
}
