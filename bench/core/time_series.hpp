#pragma once

#include <bench/core/clock.hpp>

#include <cstdint>
#include <vector>

namespace bench
{
struct sample
{
    time_point time;
    std::vector<std::int64_t> values;
};

using time_series = std::vector<sample>;
}
