#pragma once

#include <bench/core/probe_class.hpp>
#include <utils/memory.hpp>

namespace bench
{
namespace tests
{
template <typename Derived> // CRTP
class probe_template : public bench::probe
{
public:
    class probe_class : public bench::probe_class
    {
    public:
        probe_class()
        {
            name = Derived::name();
            description = Derived::description();
        }

        std::unique_ptr<bench::probe>
        create_instance(const bench::probe_config & config) const override
        {
            return utils::make_unique<Derived>(config);
        }
    };
};
}
}
