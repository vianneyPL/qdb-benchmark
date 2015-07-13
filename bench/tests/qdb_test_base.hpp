#pragma once

#include <bench/tests/test_instance_impl.hpp>

#include <qdb/client.h>

#include <vector>

namespace bench {
namespace tests {

template<typename Derived>
class qdb_test_base : public test_instance_impl<Derived>
{
public:
    void init() override final
    {
        _handle = qdb_open_tcp();
        qdb_call(qdb_connect, _config.cluster_uri.c_str());
        do_init();
    }

    void cleanup() override final
    {
        do_cleanup();
        qdb_call(qdb_close);
    }

    virtual void do_init() = 0;
    virtual void do_cleanup() = 0;

protected:    
    qdb_handle_t _handle;
    std::vector<char> _content;

    explicit qdb_test_base(bench::test_config config)
        : test_instance_impl(config), _content(_config.content_size)
    {
    }

    template<typename Function, typename... Args>
    qdb_error_t qdb_call(Function function, Args... args) const
    {
        qdb_error_t error = function(_handle, args...);
        throw_if_error(error);
        return error;
    }

private:
    void throw_if_error(qdb_error_t err) const
    {
        if (!err) return;

        throw std::runtime_error(qdb_error(err));
    }
};

}}