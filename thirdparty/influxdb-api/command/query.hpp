#pragma once

#include "../command.hpp"

namespace idb
{
namespace api
{
namespace command
{
class query : public command<query>
{
public:
    query(const std::string & base_uri) : command(base_uri)
    {
    }
    inline void setPath()
    {
        m_url << boost::network::uri::path("/query");
    }
    inline void prepareStatement(const std::string & dbname, const std::string & statement)
    {
        m_url << boost::network::uri::query("db", dbname);
        m_url << boost::network::uri::query("q", boost::network::uri::encoded(statement));
        m_request = boost::network::http::client::request(m_url);
    }
};
}
}
}