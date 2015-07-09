#pragma once

#include "test_config.hpp"
#include "test_info.hpp"
#include "test_result.hpp"

namespace qdb {
namespace bench {
namespace core {

class test_instance
{
public:
    virtual void init() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;

    virtual const test_config& config() const = 0;
    virtual const test_info& info() const = 0;
    virtual const test_result& result() const = 0;
};

}}}