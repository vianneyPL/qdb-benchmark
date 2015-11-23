#pragma once

#include <bench/tests/mongodb/blob/put.hpp>
#include <bench/tests/mongodb/blob/get.hpp>
#include <bench/tests/mongodb/blob/update.hpp>
#include <bench/tests/mongodb/integer/add.hpp>

namespace bench
{
namespace tests
{
namespace mongodb
{
template <typename OutputIt>
void get_tests(OutputIt it)
{
    *it++ = new blob::get::test_class();
    *it++ = new blob::put::test_class();
    *it++ = new blob::update::test_class();
    *it++ = new integer::add::test_class();
}
}
}
}