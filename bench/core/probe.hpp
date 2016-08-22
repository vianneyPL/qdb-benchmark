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
        auto insert_res = _measurements.emplace(std::make_pair<std::string, measurement>(std::move(id), {name, unit}));
        if (insert_res.second)
        {
            insert_res.first->second.name = std::move(name);
            insert_res.first->second.unit = unit;
            insert_res.first->second.value.clear();
        }

        insert_res.first->second.value.resize(columns);
    }

    void set_measured_value(const std::string & id, std::size_t column, std::int64_t value)
    {
        auto it = _measurements.find(id);
        if (it == _measurements.end())
        {
            throw std::runtime_error("tried to write to an unknown probe");
        }

        if (it->second.value.size() < column)
        {
            throw std::runtime_error("probe column out of bounds");
        }

        it->second.value[column] = value;
    }

private:
    measurement_collection _measurements;
};

using probe_collection = std::vector<std::unique_ptr<probe>>;

} // namespace bench
