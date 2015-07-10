#pragma once

#include "test_instance_impl.hpp"

#include <qdb/client.h>

namespace bench {
namespace tests {

class blob_get : public test_instance_impl<blob_get>
{
    qdb_handle_t _handle;

public:
    explicit blob_get(bench::test_config config)
        : test_instance_impl(config)
    {
    }

    void init() override
    {
        _handle = qdb_open_tcp();
        qdb_connect(_handle, _config.cluster_uri.c_str());

        std::vector<char> content(_config.content_size);
        qdb_put(_handle, "alias", content.data(), content.size(), 0);
    }

    void run() const override
    {
        const char* content;
        std::size_t content_size;
        qdb_get(_handle, "alias", &content, &content_size);        
        qdb_free_buffer(_handle, content);
    }

    void cleanup() override
    {        
        qdb_remove(_handle, "alias");
    }
};

const bench::test_info bench::tests::blob_get::_info = 
{
    // "id":
    "blob_get",

    // "description":
    "Repeated qdb_get() of the same entry.",

    // "size_dependent":
    true,
};

}}