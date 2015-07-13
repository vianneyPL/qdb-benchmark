#pragma once

#include <bench/core/time_series.hpp>

#include <vector>

namespace bench {

struct test_result
{
    std::vector<time_series> threads;
};

}