#pragma once

#include <bench/tests/dummy/cleanup_fail.hpp>
#include <bench/tests/dummy/setup_fail.hpp>
#include <bench/tests/dummy/test_fail.hpp>

namespace bench
{
namespace tests
{
namespace dummy
{
template <typename OutputIt>
void get_tests(OutputIt it)
{
    *it++ = new setup_fail::test_class();
    *it++ = new test_fail::test_class();
    *it++ = new cleanup_fail::test_class();
}
}
}
}