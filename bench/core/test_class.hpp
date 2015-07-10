#pragma once

#include <memory>

#include "test_config.hpp"
#include "test_info.hpp"
#include <bench/core/test_instance.hpp>

namespace qdb {
namespace bench {

class test_class
{
public:
    virtual std::unique_ptr<test_instance> instanciate(test_config) const = 0;
    virtual const test_info& info() const = 0;
};

}}