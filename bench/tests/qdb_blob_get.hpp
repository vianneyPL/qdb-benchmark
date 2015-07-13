#pragma once

#include <bench/tests/qdb_test_base.hpp>

namespace bench {
namespace tests {

class qdb_blob_get : public qdb_test_base<qdb_blob_get>
{
public:
    explicit qdb_blob_get(bench::test_config config)
        : qdb_test_base(config)
    {
    }

    void do_init() override
    {
        std::vector<char> content(_config.content_size);
        qdb_put(_handle, "alias", content.data(), content.size(), 0);
    }

    void run() const override
    {
        const char* content;
        std::size_t content_size;
        qdb_call(qdb_get, "alias", &content, &content_size);
        qdb_free_buffer(_handle, content);
    }

    void do_cleanup() override
    {        
        qdb_call(qdb_remove, "alias");
    }
};

const bench::test_info bench::tests::qdb_blob_get::_info = 
{
    // "id":
    "qdb_blob_get",

    // "description":
    "Repeated qdb_get() of the same entry.",

    // "size_dependent":
    true,
};

}}