#include <bench/tests/test_pool.hpp>
#include <bench/tests/blob_get.hpp>
#include <bench/tests/int_add.hpp>

using namespace bench::tests;

test_pool::test_pool()
{
    _tests.push_back(blob_get::get_class());
    _tests.push_back(int_add::get_class());
}

test_pool::iterator test_pool::begin() const
{
    return _tests.begin();
}

test_pool::iterator test_pool::end() const
{
    return _tests.end();
}