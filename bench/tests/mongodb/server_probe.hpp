#pragma once

#include <bench/core/probe.hpp>
#include <bench/tests/mongodb/mongodb_facade.hpp>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

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
        _node_uris = 
            mongodb_facade::resolve_topology(
                server_probe::first_node(_cluster_uri));
    }

    void take_sample(time_point now, result_type & result) override
    {
        std::vector<std::int64_t> vm_used;
        std::vector<std::int64_t> resident_size;

        std::vector<std::int64_t> storage_size;
        std::vector<std::int64_t> objects;        

        for (auto node : _node_uris) {
            auto server_status = mongodb_facade::server_status(node);

            vm_used.push_back(server_probe::mb_to_bytes(server_status["server"]["mem"]["virtual"].Int()));
            resident_size.push_back(server_probe::mb_to_bytes(server_status["server"]["mem"]["resident"].Int()));
            
            storage_size.push_back(static_cast<std::int64_t>(server_status["db"]["storageSize"].Double()));
            objects.push_back(server_status["db"]["objects"].Int());
        }

        result["vm_used"].push_back({now, vm_used});
        result["resident_size"].push_back({now, resident_size});
        result["server_storage_size"].push_back({now, storage_size});
        result["server_objects"].push_back({now, objects});
    }

    void cleanup() override
    {
    }

private:
    // Returns the first node of a cluster uri
    static std::string first_node(std::string const & cluster_uri) {
        // TODO: this assumes the cluster uri is just a single node.
        return cluster_uri;        
    }    

    static std::int64_t mb_to_bytes(std::int64_t mb) {
        return mb * 1024 * 1024;        
    }

    std::string _cluster_uri;
    mongodb_facade _mongodb;
    std::vector<std::string> _node_uris;
};

} // namespace mongodb
} // namespace tests
} // namespace bench
