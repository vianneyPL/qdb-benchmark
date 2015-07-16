#pragma once

#include <vector>

namespace bench {

struct test_result
{
    struct thread_data_point
    {
        unsigned long time;
        unsigned long iterations;
    };

    typedef std::vector<thread_data_point> thread_data;

    std::vector<thread_data> threads;
};

}