#pragma once

#include <chrono>

namespace bench
{
using clock = std::chrono::high_resolution_clock;
using time_point = clock::time_point;
using duration = clock::duration;
}
