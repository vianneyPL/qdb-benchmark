#pragma once

#include <vector>

namespace bench {

class time_series
{

};

struct test_result
{
    std::vector<time_series> threads;
};

}