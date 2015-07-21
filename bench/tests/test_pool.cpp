#include <bench/tests/test_pool.hpp>
#include <bench/tests/qdb_blob_get.hpp>
#include <bench/tests/qdb_blob_update.hpp>
#include <bench/tests/qdb_queue_push_back.hpp>
// #include <bench/tests/qdb_int_add.hpp>

using namespace bench::tests;

test_pool::test_pool() {
  add<qdb_blob_get>();
  add<qdb_blob_update>();
  add<qdb_queue_push_back>();
  // add<qdb_int_add>();
}

template <typename Test>
void test_pool::add() {
  _tests.emplace_back(std::make_unique<typename Test::test_class>());
}
