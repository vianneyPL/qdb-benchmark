#pragma once

#include <chrono>

namespace bench
{

using clock = std::chrono::high_resolution_clock;
using duration = clock::duration;
using time_point = clock::time_point;

} // namespace bench
