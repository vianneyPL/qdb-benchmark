#pragma once

#include <bench/core/clock.hpp>
#include <bench/core/probe_config.hpp>
#include <bench/core/time_series.hpp>

#include <map>
#include <memory>
#include <vector>

namespace bench
{
using probe_result = std::map<std::string, time_series>;

class probe_instance
{
public:
    virtual ~probe_instance()
    {
    }

    virtual void take_sample(time_point) = 0;

    probe_result result;
};

using probe_instance_collection = std::vector<std::unique_ptr<probe_instance>>;
}
