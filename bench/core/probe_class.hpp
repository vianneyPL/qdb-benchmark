#pragma once

#include <bench/core/probe_config.hpp>
#include <bench/core/probe_instance.hpp>

#include <memory>
#include <vector>

namespace bench
{
class probe_class
{
public:
    std::string name;
    std::string description;

    virtual std::unique_ptr<probe_instance> create_instance(const probe_config &) const = 0;
};

using probe_class_collection = std::vector<probe_class *>;
}
