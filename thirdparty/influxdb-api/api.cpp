#include "api.hpp"
#include "command/create.hpp"
#include "command/drop.hpp"
#include "command/insert.hpp"
#include "command/query.hpp"
#include <cppformat/ostream.h>
#include <iomanip>

// using namespace = influxdb::api;

void idb::api::api::create()
{
    auto create = command::create(m_base_uri);
    create.prepare(m_dbname);
    try
    {
        execute(create);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void idb::api::api::create(const measurement::measurement & mes)
{
    auto create = command::insert(m_base_uri);
    create.prepare(m_dbname, mes);
    try
    {
        execute(create);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void idb::api::api::create(const measurement::measurements & mes)
{
    auto create = command::insert(m_base_uri);
    create.prepare(m_dbname, mes);
    try
    {
        execute(create);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void idb::api::api::drop()
{
    auto drop = command::drop(m_base_uri);
    drop.prepare(m_dbname);
    try
    {
        execute(drop);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void idb::api::api::drop(const measurement::measurement & measurement)
{
    auto drop = command::query(m_base_uri);
    fmt::MemoryWriter statement;
    statement << "DROP MEASUREMENT " << std::quoted(measurement.name());
    drop.prepare(m_dbname, statement.str());
    try
    {
        execute(drop);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void idb::api::api::select(const measurement::measurement & measurement)
{
    auto select = command::query(m_base_uri);
    fmt::MemoryWriter statement;
    statement << "SELECT * FROM " << std::quoted(measurement.name());
    select.prepare(m_dbname, statement.str());
    try
    {
        execute(select);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}

void idb::api::api::select(const std::string & what, const std::string & from, const std::string & where)
{
    auto select = command::query(m_base_uri);
    fmt::MemoryWriter statement;
    statement << "SELECT " << what << " FROM " << from << " WHERE " << where;
    select.prepare(m_dbname, statement.str());
    try
    {
        execute(select);
    }
    catch (...)
    {
        std::rethrow_exception(std::current_exception());
    }
}