#pragma once

#include <bench/tests/test_template.hpp>
#include <utils/random.hpp>

#include <qdb/client.h>

#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>

namespace bench
{
namespace tests
{
namespace qdb
{
template <typename Derived>
class test_base : public test_template<Derived>
{
public:
    test_base(test_config config) : _config(config)
    {
        _alias = create_unique_alias();
        _handle = qdb_open_tcp();
        qdb_call(qdb_connect, _config.cluster_uri.c_str());
    }

    ~test_base() override
    {
        qdb_call(qdb_close);
    }

protected:
    std::string _alias;
    qdb_handle_t _handle;
    test_config _config;

    template <typename Function, typename... Args>
    qdb_error_t qdb_call(Function function, Args... args) const
    {
        qdb_error_t error = function(_handle, args...);
        throw_if_error(error);
        return error;
    }

private:
    void throw_if_error(qdb_error_t err) const
    {
        if (!err)
            return;

        throw std::runtime_error(qdb_error(err));
    }

    static std::string create_unique_alias()
    {
        static int alias_counter;
        std::ostringstream s;

        s << "benchmarks-";
        s << std::chrono::duration_cast<std::chrono::seconds>(
                 std::chrono::steady_clock::now().time_since_epoch()).count();
        s << "-" << alias_counter;

        alias_counter++;

        return s.str();
    }
};
}
}
}
