#pragma once

#include <bench/probes/probe_template.hpp>
#include <utils/qdb_wrapper.hpp>
#include <rapidjson/document.h>

namespace bench
{
namespace probes
{
namespace qdb
{
class node_status : public probe_template<node_status>
{
public:
    node_status(const probe_config & cfg) : _config(cfg)
    {
    }

    static std::string name()
    {
        return "qdb_node_status";
    }

    static std::string description()
    {
        return "Memory usage of a node";
    }

    void take_sample(time_point now) override
    {
        utils::qdb_buffer json = _qdb.node_status(_config.node_uri);

        rapidjson::Document doc;
        doc.Parse(json.data());

        result["node_memory"].push_back({now, {doc["memory"]["vm"]["used"].GetInt64()}});
        result["persisted_size"].push_back({now, {doc["entries"]["persisted"]["size"].GetInt64()}});
        result["resident_size"].push_back({now, {doc["entries"]["resident"]["size"].GetInt64()}});
    }

private:
    probe_config _config;
    utils::qdb_wrapper _qdb;
};
}
}
}
