#include <utils/qdb_wrapper.hpp>

#include <qdb/blob.h>
#include <qdb/deque.h>
#include <qdb/integer.h>

#define ARG0(x, ...) x
#define STR0(x) #x
#define STR1(x) STR0(x)

#define call(...) call(STR1(ARG0(__VA_ARGS__, )), __VA_ARGS__)

utils::qdb_wrapper::qdb_wrapper()
{
    _handle = qdb_open_tcp();
}

utils::qdb_wrapper::~qdb_wrapper()
{
    call(qdb_close);
}

void utils::qdb_wrapper::connect(const std::string & cluster_uri)
{
    call(qdb_connect, cluster_uri.c_str());
}

void utils::qdb_wrapper::free_buffer(const char * buffer)
{
    qdb_free_buffer(_handle, buffer);
}

utils::qdb_buffer utils::qdb_wrapper::node_status(const std::string & node_uri)
{
    const char * content;
    size_t content_size;
    call(qdb_node_status, node_uri.c_str(), &content, &content_size);
    return qdb_buffer(_handle, content, content_size);
}

void utils::qdb_wrapper::blob_put(const std::string & alias, const std::string & content)
{
    call(qdb_blob_put, alias.c_str(), content.data(), content.size(), 0);
}

void utils::qdb_wrapper::blob_update(const std::string & alias, const std::string & content)
{
    call(qdb_blob_update, alias.c_str(), content.data(), content.size(), 0);
}

utils::qdb_buffer utils::qdb_wrapper::blob_get(const std::string & alias)
{
    const char * result;
    std::size_t result_size;
    call(qdb_blob_get, alias.c_str(), &result, &result_size);
    return qdb_buffer(_handle, result, result_size);
}

void utils::qdb_wrapper::blob_get_noalloc(const std::string & alias, std::string & content)
{
    std::size_t result_size = content.capacity();
    call(qdb_blob_get_noalloc, alias.c_str(), const_cast<char *>(content.data()), &result_size);
    content.resize(result_size);
}

void utils::qdb_wrapper::remove(const std::string & alias)
{
    call(qdb_remove, alias.c_str());
}

utils::qdb_buffer utils::qdb_wrapper::deque_pop_back(const std::string & alias)
{
    const char * result;
    std::size_t result_size;
    call(qdb_deque_pop_back, alias.c_str(), &result, &result_size);
    return qdb_buffer(_handle, result, result_size);
}

utils::qdb_buffer utils::qdb_wrapper::deque_pop_front(const std::string & alias)
{
    const char * result;
    std::size_t result_size;
    call(qdb_deque_pop_front, alias.c_str(), &result, &result_size);
    return qdb_buffer(_handle, result, result_size);
}

void utils::qdb_wrapper::deque_push_back(const std::string & alias, const std::string & content)
{
    call(qdb_deque_push_back, alias.c_str(), content.data(), content.size());
}

void utils::qdb_wrapper::deque_push_front(const std::string & alias, const std::string & content)
{
    call(qdb_deque_push_front, alias.c_str(), content.data(), content.size());
}

std::int64_t utils::qdb_wrapper::int_add(const std::string & alias, std::int64_t value)
{
    std::int64_t total;
    call(qdb_int_add, alias.c_str(), 1, &total);
    return total;
}

void utils::qdb_wrapper::int_put(const std::string & alias, std::int64_t value)
{
    call(qdb_int_put, alias.c_str(), value, 0);
}

void utils::qdb_wrapper::int_update(const std::string & alias, std::int64_t value)
{
    call(qdb_int_update, alias.c_str(), value, 0);
}

std::int64_t utils::qdb_wrapper::int_get(const std::string & alias)
{
    std::int64_t value;
    call(qdb_int_get, alias.c_str(), &value);
    return value;
}