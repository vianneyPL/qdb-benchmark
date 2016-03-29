#pragma once

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
#include <bench/tests/qdb/hset/remove.hpp>
#include <bench/tests/qdb/integer/add.hpp>
#include <bench/tests/qdb/integer/get.hpp>
#include <bench/tests/qdb/integer/put.hpp>
#include <bench/tests/qdb/integer/remove.hpp>
#include <bench/tests/qdb/integer/update.hpp>
#include <bench/tests/qdb/stream/write.hpp>
#include <bench/tests/qdb/tag/add_blob.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{

template <typename OutputIt>
void get_tests(OutputIt it)
{
    *it++ = new qdb::blob::add_tag::test_class();
    *it++ = new qdb::blob::get::test_class();
    *it++ = new qdb::blob::get_noalloc::test_class();
    *it++ = new qdb::blob::put::test_class();
    *it++ = new qdb::blob::remove::test_class();
    *it++ = new qdb::blob::update::test_class();
    *it++ = new qdb::deque::pop_back::test_class();
    *it++ = new qdb::deque::pop_front::test_class();
    *it++ = new qdb::deque::push_back::test_class();
    *it++ = new qdb::deque::push_front::test_class();
    *it++ = new qdb::hset::contains::test_class();
    *it++ = new qdb::hset::erase::test_class();
    *it++ = new qdb::hset::insert::test_class();
    *it++ = new qdb::hset::remove::test_class();
    *it++ = new qdb::integer::add::test_class();
    *it++ = new qdb::integer::get::test_class();
    *it++ = new qdb::integer::put::test_class();
    *it++ = new qdb::integer::remove::test_class();
    *it++ = new qdb::integer::update::test_class();
    *it++ = new qdb::stream::write::test_class();
    *it++ = new qdb::tag::add_blob::test_class();
}

} // namespace qdb
} // namespace tests
} // namespace bench