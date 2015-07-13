#pragma once

#include <bench/tests/qdb_test_base.hpp>

#include <qdb/client.h>
#include <qdb/integer.h>

namespace bench {
namespace tests {

class qdb_int_add : public qdb_test_base<qdb_int_add>
{
public:
    explicit qdb_int_add(bench::test_config config)
        : qdb_test_base(config)
    {
    }

    void do_init() override
    {
        qdb_call(qdb_int_put, "alias", 0, 0);
    }

    void run() const override
    {
        qdb_int total;
        qdb_call(::qdb_int_add, "alias", 1, &total);
    }

    void do_cleanup() override
    {        
        qdb_call(qdb_remove, "alias");
    }
};

const bench::test_info bench::tests::qdb_int_add::_info = 
{
    // "id":
    "qdb_int_add",

    // "description":
    "Repeated qdb_int_add() of the same entry.",

    // "size_dependent":
    false,
};

}}