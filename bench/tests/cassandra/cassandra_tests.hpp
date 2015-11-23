#pragma once

#include <bench/tests/cassandra/blob/put.hpp>
#include <bench/tests/cassandra/blob/get.hpp>
#include <bench/tests/cassandra/blob/update.hpp>

namespace bench
{
namespace tests
{
namespace cassandra
{
template <typename OutputIt>
void get_tests(OutputIt it)
{
    *it++ = new blob::put::test_class();
    *it++ = new blob::get::test_class();
    *it++ = new blob::update::test_class();
}
}
}
}