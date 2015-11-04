#include <bench/tests/all_tests.hpp>
#include <bench/tests/dummy/cleanup_fail.hpp>
#include <bench/tests/dummy/setup_fail.hpp>
#include <bench/tests/dummy/test_fail.hpp>
#include <bench/tests/qdb/blob/add_tag.hpp>
#include <bench/tests/qdb/blob/get.hpp>
#include <bench/tests/qdb/blob/get_noalloc.hpp>
#include <bench/tests/qdb/blob/put.hpp>
#include <bench/tests/qdb/blob/remove.hpp>
#include <bench/tests/qdb/blob/update.hpp>
#include <bench/tests/qdb/deque/pop_back.hpp>
#include <bench/tests/qdb/deque/pop_front.hpp>
#include <bench/tests/qdb/deque/push_back.hpp>
#include <bench/tests/qdb/deque/push_front.hpp>
#include <bench/tests/qdb/hset/contains.hpp>
#include <bench/tests/qdb/hset/erase.hpp>
#include <bench/tests/qdb/hset/insert.hpp>
#include <bench/tests/qdb/integer/add.hpp>
#include <bench/tests/qdb/integer/get.hpp>
#include <bench/tests/qdb/integer/put.hpp>
#include <bench/tests/qdb/integer/remove.hpp>
#include <bench/tests/qdb/integer/update.hpp>
#include <bench/tests/qdb/stream/write.hpp>
#include <bench/tests/qdb/tag/add_blob.hpp>
#include <bench/tests/mongodb/integer/add.hpp>
#include <bench/tests/mongodb/blob/put.hpp>
#include <bench/tests/mongodb/blob/get.hpp>
#include <bench/tests/mongodb/blob/update.hpp>
#include <bench/tests/std/atomic.hpp>
#include <bench/tests/std/fread.hpp>
#include <bench/tests/std/fwrite.hpp>
#include <bench/tests/std/mutex.hpp>

bench::test_class_collection bench::tests::get_all_tests()
{
    // clang-format off
    return
    {
      // new dummy::setup_fail::test_class(),
      // new dummy::test_fail::test_class(),
      // new dummy::cleanup_fail::test_class(),
      new qdb::blob::add_tag::test_class(),
      new qdb::blob::get::test_class(),
      new qdb::blob::get_noalloc::test_class(),
      new qdb::blob::put::test_class(),
      new qdb::blob::remove::test_class(),
      new qdb::blob::update::test_class(),
      new qdb::deque::pop_back::test_class(),
      new qdb::deque::pop_front::test_class(),
      new qdb::deque::push_back::test_class(),
      new qdb::deque::push_front::test_class(),
      new qdb::hset::contains::test_class(),
      new qdb::hset::erase::test_class(),
      new qdb::hset::insert::test_class(),
      new qdb::integer::add::test_class(),
      new qdb::integer::get::test_class(),
      new qdb::integer::put::test_class(),
      new qdb::integer::remove::test_class(),
      new qdb::integer::update::test_class(),
      new qdb::stream::write::test_class(),
      // new qdb::tag_add_blob::test_class(),
      new mongodb::integer::add::test_class(),
      new mongodb::blob::put::test_class(),
      new mongodb::blob::get::test_class(),
      new mongodb::blob::update::test_class(),
      new std_::atomic::test_class(),
      new std_::fread::test_class(),
      new std_::fwrite::test_class(),
      new std_::mutex::test_class(),
    };
    // clang-format on
}
