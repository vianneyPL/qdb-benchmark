#pragma once

#include <bench/tests/qdb/test_base.hpp>
#include <utils/random.hpp>

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
        qdb_call(qdb_int_put, _alias.c_str(), 0, 0);
    }

    void run() override
    {
        qdb_int total;
        qdb_call(qdb_int_add, _alias.c_str(), 1, &total);
    }

    ~int_add() override
    {
        qdb_call(qdb_remove, _alias.c_str());
    }

    static std::string id()
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
