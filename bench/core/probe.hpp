#pragma once

#include <bench/core/clock.hpp>
#include <bench/core/time_series.hpp>

#include <map>
#include <memory>
#include <vector>

namespace bench
{
class probe
{
public:
    using result_type = std::map<std::string, time_series>;

    virtual void setup() = 0;
    virtual void take_sample(time_point, result_type & result) = 0;
    virtual void cleanup() = 0;

    virtual ~probe()
    {
    }
};

using probe_collection = std::vector<std::unique_ptr<probe>>;
}
