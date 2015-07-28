#pragma once

#include <bench/core/probe_code.hpp>
#include <bench/core/probe_class.hpp>
#include <utils/memory.hpp>

namespace bench
{
namespace probes
{
template <typename Derived> // CRTP
class probe_template : public bench::probe_code
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

        std::unique_ptr<bench::probe_code>
        create_code(const bench::probe_config & config) const override
        {
            return utils::make_unique<Derived>(config);
        }
    };
};
}
}
