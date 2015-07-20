#pragma once

#include <string>
#include <vector>

namespace bench {
namespace app {

struct settings
{
    std::string cluster_uri;
    std::vector<int> thread_counts;
    std::vector<int> content_sizes;
    std::vector<std::string> tests;
};

}}