#pragma once

#include <bench/core/probe.hpp>
#include <bench/tests/cassandra/cassandra_facade.hpp>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace bench
{
namespace tests
{
namespace cassandra
{

class server_probe : public probe
{
public:
    server_probe(std::string cluster_uri) : _cluster_uri(cluster_uri)
    {
    }

    void setup() override
    {
        _nodes = cassandra_facade::resolve_topology(server_probe::first_node(_cluster_uri));

        // Nothing yet
    }

    void take_sample() override
    {
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

    std::string _cluster_uri;
    cassandra_facade _cassandra;
    std::vector<std::string> _nodes;
};

} // namespace cassandra
} // namespace tests
} // namespace bench
