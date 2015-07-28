#pragma once

#include <bench/core/probe_config.hpp>
#include <bench/core/probe_code.hpp>
#include <bench/core/time_series.hpp>

#include <memory>

namespace bench
{
using probe_result = time_series<unsigned long>;

struct probe_instance
{
    probe_instance(const probe_class & cls, const probe_config & cfg) : pclass(cls), config(cfg)
    {
    }

    const probe_class & pclass;
    probe_result result;
    probe_config config;
};

inline probe_instance create_probe_instance(const probe_class & cls, probe_config cfg)
{
    return probe_instance(cls, cfg);
}

inline std::unique_ptr<probe_code> create_probe_code(const probe_instance & probe)
{
    return probe.pclass.create_code(probe.config);
}
}
