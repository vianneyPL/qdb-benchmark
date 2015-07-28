#pragma once

#include <bench/core/test_class.hpp>
#include <bench/core/test_code.hpp>
#include <bench/core/time_series.hpp>

namespace bench
{
using test_result = time_series<unsigned long>;

class test_instance
{
public:
    test_instance(const test_class & cls, test_config cfg) : tclass(cls), config(cfg)
    {
    }

    const test_class & tclass;
    test_config config;
    test_result result;
    clock::time_point start_time;
};

inline test_instance create_test_instance(const test_class & cls, test_config cfg)
{
    return test_instance(cls, cfg);
}

inline std::unique_ptr<test_code> create_test_code(const test_instance & instance)
{
    return instance.tclass.create_code(instance.config);
}
}
