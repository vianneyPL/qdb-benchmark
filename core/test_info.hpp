#pragma once

#include <string>

namespace qdb {
namespace benchmark {
namespace core {

struct test_info
{
    std::string id;
    std::string description;
    bool size_dependent;
};

}}}