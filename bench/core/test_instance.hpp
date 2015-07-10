#pragma once

#include <bench/core/test_config.hpp>
#include <bench/core/test_info.hpp>
#include <bench/core/test_result.hpp>

namespace bench {

class test_instance
{
public:
    test_result result;

    virtual void init() = 0;
    virtual void run() const = 0;
    virtual void cleanup() = 0;

    virtual const test_config& config() const = 0;
    virtual const test_info& info() const = 0;    
};

}