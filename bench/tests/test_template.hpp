#pragma once

#include <bench/core/test_class.hpp>
#include <bench/core/test_runner.hpp>
#include <utils/memory.hpp>

namespace bench
{
namespace tests
{
template <typename Derived> // CRTP
class test_template : public bench::test_runner
{
public:
    class test_class : public bench::test_class
    {
    public:
        test_class()
        {
            id = Derived::id();
            description = Derived::description();
            size_dependent = Derived::size_dependent();
        }

        std::unique_ptr<bench::test_runner> create_runner(bench::test_config config) const override
        {
            return utils::make_unique<Derived>(config);
        }
    };

    static const bench::test_class * get_class()
    {
        static test_class cls;
        return &cls;
    }
};
}
}
