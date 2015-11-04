#include <iostream>

#include <bench/tests/mongodb/mongodb_facade.hpp>
#include <mongo/bson/bson.h>

#define NAMESPACE "bench.objects"

// Calls MongoDB function, checks for error and discards result
#define CHECK_ERROR(func, conn, ...)         \
    conn.func(__VA_ARGS__);                  \
                                             \
    std::string error = conn.getLastError(); \
    if (error != "") throw std::runtime_error(#func + error);

// Calls MongoDB function, checks for error and store result in `result`
#define CHECK_ERROR_STORE(func, conn, result, ...) \
    auto result = conn.func(__VA_ARGS__);          \
                                                   \
    std::string error = conn.getLastError();       \
    if (error != "") throw std::runtime_error(#func + error);

utils::mongodb_facade::mongodb_facade()
{
    // :TODO: make runtime configurable
    _conn.connect("localhost");
}

utils::mongodb_facade::~mongodb_facade()
{
}

void utils::mongodb_facade::remove(const std::string & alias)
{
    CHECK_ERROR(remove, _conn, NAMESPACE, MONGO_QUERY("_id" << alias), true, NULL);
}

void utils::mongodb_facade::blob_put(const std::string & alias, const std::string & content)
{
    CHECK_ERROR(insert, _conn, NAMESPACE, BSON("_id" << alias << "content" << content));
}

void utils::mongodb_facade::blob_update(const std::string & alias, const std::string & content)
{
    CHECK_ERROR(findAndModify, _conn, NAMESPACE, BSON("_id" << alias), BSON("content" << content),
                false, true);
}

std::string utils::mongodb_facade::blob_get(const std::string & alias)
{
    CHECK_ERROR_STORE(query, _conn, cursor, NAMESPACE, MONGO_QUERY("_id" << alias));

    return cursor->next().getField("content").String();
}

void utils::mongodb_facade::int_put(const std::string & alias, std::int64_t value)
{
    CHECK_ERROR(insert, _conn, NAMESPACE,
                BSON("_id" << alias << "num" << static_cast<long long>(value)));
}

std::int64_t utils::mongodb_facade::int_add(const std::string & alias, std::int64_t value)
{
    CHECK_ERROR_STORE(findAndModify, _conn, obj, NAMESPACE, BSON("_id" << alias),
                      BSON("$inc" << BSON("num" << static_cast<long long>(value))), false, true);

    return obj.getField("num").Long();
}
