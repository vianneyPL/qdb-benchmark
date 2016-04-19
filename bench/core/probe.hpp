#pragma once

#include <bench/core/unit.hpp>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace bench
{

struct measurement
{
    std::string name;
    bench::unit unit;
    std::vector<std::int64_t> value;
};

using measurement_collection = std::map<std::string, measurement>;

class probe
{
public:
    virtual void setup() = 0;
    virtual void take_sample() = 0;
    virtual void cleanup() = 0;

    virtual ~probe()
    {
    }

    const measurement_collection & measurements() const
    {
        return _measurements;
    }

protected:
    void define_measurement(std::string id, std::string name, bench::unit unit, std::size_t columns)
    {
        _measurements[id] = {name, unit};
        _measurements[id].value.resize(columns);
    }

    void set_measured_value(std::string id, std::size_t column, std::int64_t value)
    {
        _measurements[id].value[column] = value;
    }

private:
    measurement_collection _measurements;
};

using probe_collection = std::vector<std::unique_ptr<probe>>;

} // namespace bench
