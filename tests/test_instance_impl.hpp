#pragma once

#include "test_class.hpp"
#include "test_instance.hpp"

#include <memory>

namespace qdb {
namespace bench {
namespace tests {

template<typename Derived> // CRTP
class test_instance_impl : public qdb::bench::core::test_instance
{
    class test_class_impl : public qdb::bench::core::test_class
    {
    public:
        std::unique_ptr<qdb::bench::core::test_instance> instanciate(qdb::bench::core::test_config config) const override
        {
            return std::make_unique<Derived>(config);
        }

        const qdb::bench::core::test_info& info() const override
        {
            return test_instance_impl::_info;
        }
    };

public:
    const qdb::bench::core::test_config& config() const override
    {
        return _config;
    }

    const qdb::bench::core::test_info& info() const override
    {
        return _info;
    }

    const qdb::bench::core::test_result& result() const  override
    {
        return _result;
    }

    static const qdb::bench::core::test_class* get_class()
    {
        static test_class_impl cls;
        return &cls;
    }

protected:
    explicit test_instance_impl(qdb::bench::core::test_config config)
        : _config(config)
    {
    }

    const qdb::bench::core::test_config _config;
    const qdb::bench::core::test_result _result;
    const static qdb::bench::core::test_info _info;
};

}}}

