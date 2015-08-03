#pragma once

#include <bench/core/test_config.hpp>
#include <bench/core/test_code.hpp>
#include <bench/core/probe.hpp>

#include <memory>
#include <vector>

namespace bench
{
class test_class
{
public:
    std::string name;
    std::string description;
    bool size_dependent;

    virtual std::unique_ptr<test_code> create_code(test_config) const = 0;
    virtual probe_collection create_probes(test_config) const = 0;
};

typedef std::vector<const test_class *> test_class_collection;
}
