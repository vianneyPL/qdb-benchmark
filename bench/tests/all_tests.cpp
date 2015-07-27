#include <bench/tests/all_tests.hpp>
#include <bench/tests/qdb/blob_get.hpp>
#include <bench/tests/qdb/blob_update.hpp>
#include <bench/tests/qdb/int_add.hpp>
#include <bench/tests/qdb/int_update.hpp>
#include <bench/tests/qdb/queue_push_back.hpp>

bench::test_collection bench::tests::get_all_tests()
{
    return {
        new qdb::blob_get::test_class(),
        new qdb::blob_update::test_class(),
        new qdb::int_add::test_class(),
        new qdb::int_update::test_class(),
        new qdb::queue_push_back::test_class(),
    };
}
