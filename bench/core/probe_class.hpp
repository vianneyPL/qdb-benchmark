#pragma once

#include <bench/core/probe_config.hpp>
#include <bench/core/probe_code.hpp>

#include <memory>
#include <vector>

namespace bench
{
class probe_class
{
public:
    std::string name;
    std::string description;

    virtual std::unique_ptr<probe_code> create_code(const probe_config &) const = 0;
};

using probe_collection = std::vector<probe_class *>;
}
