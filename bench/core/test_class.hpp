#pragma once

#include <memory>

#include <bench/core/test_config.hpp>
#include <bench/core/test_code.hpp>

namespace bench
{
class test_class
{
public:
    std::string name;
    std::string description;
    bool size_dependent;

    virtual std::unique_ptr<test_code> create_code(test_config) const = 0;
};
}
