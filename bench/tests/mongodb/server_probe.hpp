#pragma once

#include <bench/core/probe.hpp>
#include <bench/tests/mongodb/mongodb_facade.hpp>
#include <algorithm>

namespace bench
{
namespace tests
{
namespace mongodb
{

class server_probe : public probe
{
public:
    server_probe(std::string cluster_uri) : _cluster_uri(cluster_uri)
    {
    }

    void setup() override
    {
        _nodes = mongodb_facade::resolve_topology(server_probe::first_node(_cluster_uri));

        std::size_t columns = _nodes.size();

        define_measurement("mongodb.server.vm_used", "MongoDB: Virtual Memory", unit::bytes, columns);
        define_measurement("mongodb.server.resident_size", "MongoDB: Resident Size", unit::bytes, columns);
        define_measurement("mongodb.server.storage_size", "MongoDB: Server Storage Size", unit::bytes, columns);
        define_measurement("mongodb.server.objects", "MongoDB: Server Objects", unit::bytes, columns);
    }

    void take_sample() override
    {
        for (std::size_t i = 0; i < _nodes.size(); i++)
        {
            auto status = mongodb_facade::server_status(_nodes[i]);

            // clang-format off
            set_measured_value("mongodb.server.vm_used",       i, server_probe::mb_to_bytes(status["server"]["mem"]["virtual"].Int()));
            set_measured_value("mongodb.server.resident_size", i, server_probe::mb_to_bytes(status["server"]["mem"]["resident"].Int()));
            set_measured_value("mongodb.server.storage_size",  i, static_cast<std::int64_t>(status["db"]["storageSize"].Double()));
            set_measured_value("mongodb.server.objects",       i,                           status["db"]["objects"].Int());
            // clang-format on
        }
    }

    void cleanup() override
    {
    }

private:
    // Returns the first node of a cluster uri
    static std::string first_node(std::string const & cluster_uri)
    {
        // TODO: this assumes the cluster uri is just a single node.
        return cluster_uri;
    }

    static std::int64_t mb_to_bytes(std::int64_t mb)
    {
        return mb * 1024 * 1024;
    }

    std::string _cluster_uri;
    mongodb_facade _mongodb;
    std::vector<std::string> _nodes;
};

} // namespace mongodb
} // namespace tests
} // namespace bench
