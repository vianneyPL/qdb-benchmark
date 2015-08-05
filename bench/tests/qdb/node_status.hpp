#pragma once

#include <bench/core/probe.hpp>
#include <utils/qdb_wrapper.hpp>
#include <rapidjson/document.h>

namespace bench
{
namespace tests
{
namespace qdb
{
class node_status : public probe
{
public:
    node_status(std::string cluster_uri) : _cluster_uri(cluster_uri)
    {
    }

    void setup() override
    {
    }

    void take_sample(time_point now, result_type & result) override
    {
        utils::qdb_buffer json = _qdb.node_status(_cluster_uri);

        rapidjson::Document doc;
        doc.Parse(json.data());

        result["node_memory"].push_back({now, {doc["memory"]["vm"]["used"].GetInt64()}});
        result["persisted_size"].push_back({now, {doc["entries"]["persisted"]["size"].GetInt64()}});
        result["resident_size"].push_back({now, {doc["entries"]["resident"]["size"].GetInt64()}});
    }

    void cleanup() override
    {
    }

private:
    std::string _cluster_uri;
    utils::qdb_wrapper _qdb;
};
}
}
}
