#pragma once

#include "../command.hpp"

namespace idb
{
namespace api
{
namespace command
{
class insert : public command<insert>
{
    using uri = boost::network::uri::uri;

public:
    using tag = execution_tag::post;
    insert(const std::string & base_uri) : command(base_uri)
    {
    }
    inline void setPath()
    {
        m_url << boost::network::uri::path("/write");
    }
    inline void prepareStatement(const std::string & dbname, const measurement::measurement & measurement)
    {
        m_url << boost::network::uri::query("db", dbname);
        m_request = boost::network::http::client::request(m_url);
        auto line = measurement.line();
        m_request << boost::network::header("Content-Length", std::to_string(line.size()));
        m_request.body(line);
    }
    inline void prepareStatement(const std::string & dbname, const measurement::measurements & measurement)
    {
        m_url << boost::network::uri::query("db", dbname);
        m_request = boost::network::http::client::request(m_url);
        auto line = measurement.line();
        m_request << boost::network::header("Content-Length", std::to_string(line.size()));
        m_request.body(line);
    }
};
}
}
}