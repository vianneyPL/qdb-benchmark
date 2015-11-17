#pragma once

#include <bench/core/probe.hpp>
#include <snmp/sys_info.hpp>

#include <string>
#include <vector>

namespace bench
{
namespace framework
{
class snmp_probe : public probe
{
public:
    snmp_probe(const std::vector<std::string> & peernames)
    {
        for (auto & peername : peernames)
            _peers.emplace_back(peername);
    }

    void setup() override
    {
        for (auto & peer : _peers)
        {
            peer.connect();
        }

        // clang-format off
        define_measurement<snmp::sys_info::physical_memory>("snmp.physical_memory", "SNMP: Physical Memory", unit::bytes);
        define_measurement<snmp::sys_info::virtual_memory> ("snmp.virtual_memory",  "SNMP: Virtual Memory",  unit::bytes);
        define_measurement<snmp::sys_info::cached_memory>  ("snmp.cached_memory",   "SNMP: Cached Memory",   unit::bytes);
        define_measurement<snmp::sys_info::swap_space>     ("snmp.swap_space",      "SNMP: Swap Space",      unit::bytes);
        define_measurement<snmp::sys_info::fixed_disks>    ("snmp.fixed_disks",     "SNMP: Fixed Disks",     unit::bytes);
        // clang-format on
    }

    void take_sample() override
    {
        for (auto & peer : _peers)
        {
            peer.update();
        }

        take_sample<snmp::sys_info::physical_memory>("snmp.physical_memory");
        take_sample<snmp::sys_info::virtual_memory>("snmp.virtual_memory");
        take_sample<snmp::sys_info::cached_memory>("snmp.cached_memory");
        take_sample<snmp::sys_info::swap_space>("snmp.swap_space");
        take_sample<snmp::sys_info::fixed_disks>("snmp.fixed_disks");
    }

    void cleanup() override
    {
        for (auto & peer : _peers)
        {
            peer.close();
        }
    }

private:
    template <typename InformationType>
    void define_measurement(std::string id, std::string name, bench::unit unit)
    {
        for (auto & peer : _peers)
        {
            if (peer.supports<InformationType>())
            {
                probe::define_measurement(id, name, unit, _peers.size());
            }
        }
    }

    template <typename InformationType>
    void take_sample(const std::string & id)
    {
        std::vector<std::int64_t> values;

        for (std::size_t i = 0; i < _peers.size(); i++)
        {
            if (_peers[i].supports<InformationType>())
            {
                set_measured_value(id, i, _peers[i].get<InformationType>());
            }
        }
    }

    std::vector<snmp::sys_info> _peers;
};
}
}
