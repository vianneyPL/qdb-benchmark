#pragma once

#include <bench/core/probe_instance.hpp>
#include <bench/core/probe_code.hpp>
#include <utils/memory.hpp>

#include <chrono>
#include <iostream>

namespace bench
{
namespace framework
{
class probe_sampler
{
public:
    probe_sampler(probe_instance & probe) : _probe(probe), _code(create_probe_code(probe))
    {
    }

    probe_sampler(probe_sampler && other) : _probe(other._probe), _code(std::move(other._code))
    {
    }

    void save_sample()
    {
        sample<unsigned long> sample;
        sample.time = clock::now();
        sample.values.push_back(_code->read());
        _probe.result.emplace_back(sample);
    }

private:
    probe_instance & _probe;
    std::unique_ptr<probe_code> _code;
};
}
}
