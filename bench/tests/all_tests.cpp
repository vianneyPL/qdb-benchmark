#include <bench/tests/all_tests.hpp>
#include <bench/tests/dummy/cleanup_fail.hpp>
#include <bench/tests/dummy/setup_fail.hpp>
#include <bench/tests/dummy/test_fail.hpp>
#include <bench/tests/qdb/blob_get.hpp>
#include <bench/tests/qdb/blob_get_noalloc.hpp>
#include <bench/tests/qdb/blob_put.hpp>
#include <bench/tests/qdb/blob_remove.hpp>
#include <bench/tests/qdb/blob_update.hpp>
#include <bench/tests/qdb/deque_push_back.hpp>
#include <bench/tests/qdb/deque_push_front.hpp>
#include <bench/tests/qdb/int_add.hpp>
#include <bench/tests/qdb/int_update.hpp>
#include <bench/tests/stdio/fread.hpp>
#include <bench/tests/stdio/fwrite.hpp>

bench::test_class_collection bench::tests::get_all_tests()
{
    return {
        // new dummy::setup_fail::test_class(),
        // new dummy::test_fail::test_class(),
        // new dummy::cleanup_fail::test_class(),
        new qdb::blob_get::test_class(),
        new qdb::blob_get_noalloc::test_class(),
        new qdb::blob_put::test_class(),
        new qdb::blob_remove::test_class(),
        new qdb::blob_update::test_class(),
        new qdb::deque_push_back::test_class(),
        new qdb::deque_push_front::test_class(),
        new qdb::int_add::test_class(),
        new qdb::int_update::test_class(),
        new stdio::fread::test_class(),
        new stdio::fwrite::test_class(),
    };
}
