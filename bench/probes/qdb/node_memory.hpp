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
class node_memory : public probe_template<node_memory>
{
public:
    node_memory(const probe_config & cfg) : _config(cfg)
    {
    }

    static std::string name()
    {
        return "qdb_node_memory";
    }

    static std::string description()
    {
        return "Memory usage of a node";
    }

    probe_sample read() override
    {
        utils::qdb_buffer json = _qdb.node_status(_config.node_uri);
        rapidjson::Document doc;
        doc.Parse(json.data());
        return doc["memory"]["vm"]["used"].GetUint64();
    }

private:
    probe_config _config;
    utils::qdb_wrapper _qdb;
};
}
}
}
