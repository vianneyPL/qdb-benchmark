#pragma once

#include <bench/core/clock.hpp>
#include <bench/core/unit.hpp>
#include <cstdint>
#include <vector>

namespace bench
{

struct sample
{
    time_point time;
    std::vector<std::int64_t> values;
};

struct time_series
{
    std::string id;
    std::string name;
    bench::unit unit;
    std::vector<sample> samples;
};

} // namespace bench
