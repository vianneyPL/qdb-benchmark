#pragma once

#include <bench/core/test_class.hpp>
#include <bench/core/test_loop.hpp>
#include <bench/core/time_series.hpp>

#include <map>
#include <string>

namespace bench
{
using test_result = std::map<std::string, time_series>;

class test_instance
{
public:
    test_instance(const test_class & cls, test_config cfg) : tclass(cls), config(cfg)
    {
    }

    const test_class & tclass;
    test_config config;
    test_result result;
    time_point start_time;
    duration setup_duration;
    duration test_duration;
    duration cleanup_duration;
    std::string error;
};

using test_instance_collection = std::vector<test_instance>;

inline test_instance create_test_instance(const test_class & cls, test_config cfg)
{
    return test_instance(cls, cfg);
}

inline std::unique_ptr<test_loop> create_test_loop(const test_instance & instance)
{
    return instance.tclass.create_loop(instance.config);
}

inline probe_collection create_test_probes(const test_instance & instance)
{
    return instance.tclass.create_probes(instance.config);
}
}
