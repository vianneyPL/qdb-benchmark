#pragma once

#include <chrono>
#include <string>

namespace bench
{
struct test_config
{
    std::string cluster_uri;
    std::size_t content_size;
    std::size_t content_count;
    int thread_count;
    std::chrono::duration<int> duration;
};
}
