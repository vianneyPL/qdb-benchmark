#pragma once

#include <memory>

#include <bench/core/test_config.hpp>
#include <bench/core/test_runner.hpp>

namespace bench {

class test_class
{
public:
    std::string id;
    std::string description;
    bool size_dependent;

    virtual std::unique_ptr<test_runner> create_runner(test_config) const = 0;
};
}