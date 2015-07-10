#include <bench/tests/test_pool.hpp>
#include <bench/tests/blob_get.hpp>
#include <bench/tests/int_add.hpp>

using namespace bench::tests;

test_pool::test_pool()
{
    add<blob_get>();
    add<int_add>();
}

template<typename Test>
void test_pool::add()
{
    _tests.emplace_back(std::make_unique<Test::test_class>());
}
