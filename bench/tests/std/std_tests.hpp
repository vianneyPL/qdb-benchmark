#pragma once

#include <bench/tests/std/atomic.hpp>
#include <bench/tests/std/fread.hpp>
#include <bench/tests/std/fwrite.hpp>
#include <bench/tests/std/mutex.hpp>

namespace bench
{
namespace tests
{
namespace std_
{
template <typename OutputIt>
void get_tests(OutputIt it)
{
    *it++ = new atomic::test_class();
    *it++ = new fread::test_class();
    *it++ = new fwrite::test_class();
    *it++ = new mutex::test_class();
}
}
}
}