#pragma once

#include <bench/tests/qdb_test_base.hpp>
#include <utils/create_random_vector.hpp>

namespace bench {
namespace tests {

class qdb_blob_update : public qdb_test_base<qdb_blob_update>
{
public:
    explicit qdb_blob_update(bench::test_config config)
        : qdb_test_base(config)
    {
    }

    void do_init() override
    {
    }

    void run() const override
    {
        std::vector<char> content = utils::create_random_vector(config().content_size);

        qdb_call(qdb_update, "alias", content.data(), content.size(), 0);
    }

    void do_cleanup() override
    {        
        qdb_call(qdb_remove, "alias");
    }
};

const bench::test_info bench::tests::qdb_blob_update::_info = 
{
    // "id":
    "qdb_blob_update",

    // "description":
    "Repeated qdb_update() of the same entry.",

    // "size_dependent":
    true,
};

}}