#pragma once

#include <bench/core/test_class.hpp>
#include <bench/core/test_loop.hpp>
#include <utils/memory.hpp>

namespace bench
{
namespace tests
{
template <typename Derived> // CRTP
class test_template : public bench::test_loop
{
public:
    class test_class : public bench::test_class
    {
    public:
        test_class()
        {
            name = Derived::name();
            description = Derived::description();
            size_dependent = Derived::size_dependent();
        }

        std::unique_ptr<bench::test_loop> create_loop(bench::test_config config) const override
        {
            return utils::make_unique<Derived>(config);
        }

        probe_collection create_probes(bench::test_config config) const override
        {
            return Derived::create_probes(config);
        }
    };

    static probe_collection create_probes(bench::test_config config)
    {
        return {};
    }
};
}
}
