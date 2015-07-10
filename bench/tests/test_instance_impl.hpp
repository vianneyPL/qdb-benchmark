#pragma once

#include <bench/core/test_class.hpp>
#include <bench/core/test_instance.hpp>

#include <memory>

namespace qdb {
namespace bench {
namespace tests {

template<typename Derived> // CRTP
class test_instance_impl : public qdb::bench::test_instance
{
    class test_class_impl : public qdb::bench::test_class
    {
    public:
        std::unique_ptr<qdb::bench::test_instance> instanciate(qdb::bench::test_config config) const override
        {
            return std::make_unique<Derived>(config);
        }

        const qdb::bench::test_info& info() const override
        {
            return test_instance_impl::_info;
        }
    };

public:
    const qdb::bench::test_config& config() const override
    {
        return _config;
    }

    const qdb::bench::test_info& info() const override
    {
        return _info;
    }

    const qdb::bench::test_result& result() const  override
    {
        return _result;
    }

    static const qdb::bench::test_class* get_class()
    {
        static test_class_impl cls;
        return &cls;
    }

protected:
    explicit test_instance_impl(qdb::bench::test_config config)
        : _config(config)
    {
    }

    const qdb::bench::test_config _config;
    const qdb::bench::test_result _result;
    const static qdb::bench::test_info _info;
};

}}}

