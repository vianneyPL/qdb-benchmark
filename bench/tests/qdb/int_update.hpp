#pragma once

#include <bench/tests/qdb/test_base.hpp>

#include <qdb/integer.h>

namespace bench
{
namespace tests
{
namespace qdb
{
class int_update : public test_base<int_update>
{
    int _value;

public:
    explicit int_update(bench::test_config config) : test_base(config)
    {
        _qdb.call(qdb_int_put, _alias.c_str(), 0, 0);
    }

    void run_iteration()
    {
        _qdb.call(qdb_int_update, _alias.c_str(), ++_value, 0);
    }

    ~int_update() override
    {
        _qdb.remove(_alias);
    }

    static std::string name()
    {
        return "qdb_int_update";
    }

    static std::string description()
    {
        return "Repeated qdb_int_update() of the same entry.";
    }

    static bool size_dependent()
    {
        return false;
    }
};
}
}
}
