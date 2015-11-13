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
    }

    void take_sample(time_point now, result_type & result) override
    {
        for (auto & peer : _peers)
        {
            peer.update();
        }

        take_sample<snmp::sys_info::physical_memory>(now, result, "snmp.physical_memory");
        take_sample<snmp::sys_info::virtual_memory>(now, result, "snmp.virtual_memory");
        take_sample<snmp::sys_info::cached_memory>(now, result, "snmp.cached_memory");
        take_sample<snmp::sys_info::swap_space>(now, result, "snmp.swap_space");
        take_sample<snmp::sys_info::fixed_disks>(now, result, "snmp.fixed_disks");
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
    void take_sample(time_point now, result_type & result, const char * key)
    {
        std::vector<std::int64_t> values;

        for (auto & peer : _peers)
        {
            if (peer.supports<InformationType>())
            {
                values.push_back(peer.get<InformationType>());
            }
        }

        if (!values.empty())
        {
            result[key].push_back({now, values});
        }
    }

    std::vector<snmp::sys_info> _peers;
};
}
}
