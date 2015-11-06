#pragma once

#include <iostream>

#include <bench/core/probe.hpp>
#include <bench/tests/mongodb/mongodb_facade.hpp>
#include <rapidjson/document.h>

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

class node_status : public probe
{
public:
    node_status(std::string cluster_uri) : _cluster_uri(cluster_uri)
    {
    }

    void setup() override
    {
        _node_uris = 
            mongodb_facade::resolve_topology(
                node_status::first_node(_cluster_uri));
    }

    void take_sample(time_point now, result_type & result) override
    {
        std::vector<std::int64_t> physmem_used, vm_used, evictions;
        std::vector<std::int64_t> persisted_size, persisted_count;
        std::vector<std::int64_t> resident_size, resident_count;
        std::vector<std::int64_t> successes, failures;

        for (auto node : _node_uris) {
            auto node_status = mongodb_facade::node_status(node);

            // This is a check that the node is not using mmap(), but
            // rather the WiredTiger storage engine.
            if (node_status["server"]["storageEngine"]["name"].String() != "wiredTiger") {
                throw std::runtime_error("Benchmark requires mongodb's WiredTiger storage engine, not mmap()");
            }

            vm_used.push_back(node_status::mb_to_bytes(node_status["server"]["mem"]["virtual"].Int()));
            resident_size.push_back(node_status::mb_to_bytes(node_status["server"]["mem"]["resident"].Int()));
            
            persisted_size.push_back(static_cast<std::int64_t>(node_status["db"]["storageSize"].Double()));
            persisted_count.push_back(node_status["db"]["objects"].Int());
        }

        result["physmem_used"].push_back({now, physmem_used});
        result["vm_used"].push_back({now, vm_used});
        result["evictions"].push_back({now, evictions});
        result["persisted_size"].push_back({now, persisted_size});
        result["persisted_count"].push_back({now, persisted_count});
        result["resident_size"].push_back({now, resident_size});
        result["resident_count"].push_back({now, resident_count});
        result["successes"].push_back({now, successes});
        result["failures"].push_back({now, failures});
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
