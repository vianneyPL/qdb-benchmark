#pragma once

#include <bench/core/clock.hpp>

#include <vector>

namespace bench
{
template <typename T>
struct sample
{
    clock::time_point time;
    std::vector<T> values;
};

template <typename T>
using time_series = std::vector<sample<T>>;
}
