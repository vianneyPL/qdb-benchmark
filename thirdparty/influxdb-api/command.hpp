#pragma once

#include "measurement.hpp"
#include "measurements.hpp"
#include <boost/network/protocol/http/client.hpp>
#include <boost/network/uri.hpp>
#include <utility>

namespace idb
{
namespace api
{
namespace command
{
struct execution_tag
{
    struct get
    {
    };
    struct post
    {
    };

    // doesn't really make sense in this use case
    // since this is a time series database
    // struct put {};
};
template <typename Derived>
class command
{
    using url_type = boost::network::uri::uri;
    using http_request = boost::network::http::client::request;

public:
    using tag = execution_tag::get;

    command(const std::string & base_uri)
    {
        m_url << boost::network::uri::host(base_uri);
        static_cast<Derived *>(this)->setPath();
    }

    template <typename... Args>
    void prepare(Args... args)
    {
        static_cast<Derived *>(this)->prepareStatement(args...);
    }

    const url_type & url() const
    {
        return m_url;
    }
    const http_request & request() const
    {
        return m_request;
    }

protected:
    url_type m_url;
    http_request m_request;
};
}
}
}