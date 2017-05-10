#pragma once

#include "command.hpp"
#include <boost/network/protocol/http/client.hpp>
#include <boost/network/uri/uri_io.hpp>
#include <exception>
#include <iostream>
#include <memory>
#include <type_traits>

namespace idb
{
namespace api
{
class api
{
    using http_client = boost::network::http::client;

public:
    api() = default;
    api(const std::string & base_uri, const std::string & dbname) : m_base_uri(base_uri), m_dbname(dbname)
    {
    }
    api(const api & a) = default;
    api(api && a) = default;

    api & operator=(const api & a) = default;
    api & operator=(api && a) = default;

    template <typename QueryType>
    typename std::enable_if<std::is_base_of<command::command<QueryType>, QueryType>::value, void>::type
    execute(QueryType query)
    {
        typename QueryType::tag execution_tag;
        try
        {
            execute_impl(query, execution_tag);
        }
        catch (...)
        {
            std::rethrow_exception(std::current_exception());
        }
    }

    void createDatabase();
    void create(const measurement::measurement & measurement);
    void create(const measurement::measurements & measurements);

    void dropDatabase();
    void drop(const measurement::measurement & measurement);

    void select(const measurement::measurement & measurement);
    void select(const std::string & what, const std::string & from);
    void select(const std::string & what, const std::string & from, const std::string & where);

private:
    std::string m_base_uri;
    std::string m_dbname;
    std::shared_ptr<http_client> m_client = std::make_shared<http_client>();

    template <typename QueryType>
    void execute_impl(QueryType query, command::execution_tag::get)
    {
        try
        {
            response_handler(m_client->get(query.request()));
        }
        catch (...)
        {
            std::rethrow_exception(std::current_exception());
        }
    }

    template <typename QueryType>
    void execute_impl(QueryType query, command::execution_tag::post)
    {
        try
        {
            response_handler(m_client->post(query.request()));
        }
        catch (...)
        {
            std::rethrow_exception(std::current_exception());
        }
    }

    template <typename ResponseType>
    void response_handler(ResponseType response)
    {
        auto status = boost::network::http::status(response);
        if (status != 200 && status != 204)
        {
            auto status_message = boost::network::http::status_message(response);
            std::string message = status_message;
            message += " body: ";
            message += response.body();
            throw std::runtime_error(message);
        }
    }
};
}
}
