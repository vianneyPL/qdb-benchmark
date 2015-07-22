#pragma once

#include <bench/core/test_class.hpp>
#include <bench/core/test_result.hpp>

namespace bench
{
class test_instance
{
public:
    test_instance(const test_class & cls, test_config cfg) : tclass(cls), config(cfg)
    {
    }

    const test_class & tclass;
    test_config config;
    test_result result;
};

inline test_instance create_test_instance(const test_class & cls, test_config cfg)
{
    return test_instance(cls, cfg);
}

inline std::unique_ptr<test_runner> create_test_runner(const test_instance & instance)
{
    return instance.tclass.create_runner(instance.config);
}
}
