#pragma once

#include <bench/tests/qdb/test_base.hpp>

#include <qdb/integer.h>

namespace bench
{
namespace tests
{
namespace qdb
{
class int_add : public test_base<int_add>
{
public:
    explicit int_add(bench::test_config config) : test_base(config)
    {
    }

    void setup() override
    {
        test_base::setup();
        _qdb.call(qdb_int_put, _alias.c_str(), 0, 0);
    }

    void run() override
    {
        qdb_int_t total;
        _qdb.call(qdb_int_add, _alias.c_str(), 1, &total);
    }

    void cleanup() override
    {
        _qdb.call(qdb_remove, _alias.c_str());
        test_base::cleanup();
    }

    static std::string name()
    {
        return "qdb_int_add";
    }

    static std::string description()
    {
        return "Repeated qdb_int_add() of the same entry.";
    }

    static bool size_dependent()
    {
        return false;
    }
};
}
}
}
