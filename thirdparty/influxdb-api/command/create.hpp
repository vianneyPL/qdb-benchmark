#pragma once

#include "../command.hpp"

namespace idb
{
namespace api
{
namespace command
{
class create : public command<create>
{
public:
    create(const std::string & base_uri) : command(base_uri)
    {
    }
    inline void setPath()
    {
        m_url << boost::network::uri::path("/query");
    }
    inline void prepareStatement(const std::string & dbname)
    {
        m_url << boost::network::uri::query("q", boost::network::uri::encoded("CREATE DATABASE " + dbname));
        m_request = boost::network::http::client::request(m_url);
    }
};
}
}
}