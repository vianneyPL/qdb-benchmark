#pragma once

#include <bench/tests/test_instance_impl.hpp>

#include <qdb/client.h>
#include <qdb/integer.h>

namespace bench {
namespace tests {

class int_add : public test_instance_impl<int_add>
{
    qdb_handle_t _handle;

public:
    explicit int_add(bench::test_config config)
        : test_instance_impl(config)
    {
    }

    void init() override
    {
        _handle = qdb_open_tcp();
        qdb_connect(_handle, _config.cluster_uri.c_str());
        qdb_int_put(_handle, "alias", 0, 0);
    }

    void run() const override
    {
        qdb_int_add(_handle, "alias", 1, 0);        
    }

    void cleanup() override
    {        
        qdb_remove(_handle, "alias");
    }
};

const bench::test_info bench::tests::int_add::_info = 
{
    // "id":
    "int_add",

    // "description":
    "Repeated qdb_int_add() of the same entry.",

    // "size_dependent":
    false,
};

}}