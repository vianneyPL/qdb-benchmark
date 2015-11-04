#include <bench/tests/qdb/quasardb_facade.hpp>

#include <qdb/blob.h>
#include <qdb/deque.h>
#include <qdb/hset.h>
#include <qdb/integer.h>
#include <qdb/stream.h>
#include <qdb/tag.h>

#define ARG0(x, ...) x
#define STR0(x) #x
#define STR1(x) STR0(x)
#define CALL(...) wrap_call(STR1(ARG0(__VA_ARGS__, )), _handle, __VA_ARGS__)

static bool is_error(qdb_error_t err)
{
    switch (err)
    {
    case qdb_e_ok:
    case qdb_e_element_already_exists:
    case qdb_e_element_not_found: return false;
    default: return true;
    }
}

template <typename Function, typename Handle, typename... Args>
static qdb_error_t wrap_call(std::string name, Handle handle, Function function, Args... args)
{
    qdb_error_t err = function(handle, args...);
    if (is_error(err)) throw std::runtime_error(name + ": " + qdb_error(err));
    return err;
}

utils::quasardb_facade::quasardb_facade()
{
    _handle = qdb_open_tcp();
}

utils::quasardb_facade::~quasardb_facade()
{
    CALL(qdb_close);
}

void utils::quasardb_facade::connect(const std::string & cluster_uri)
{
    CALL(qdb_connect, cluster_uri.c_str());
}

void utils::quasardb_facade::free_buffer(const char * buffer)
{
    qdb_free_buffer(_handle, buffer);
}

utils::qdb_buffer utils::quasardb_facade::node_status(const std::string & node_uri) const
{
    const char * content;
    size_t content_size;
    CALL(qdb_node_status, node_uri.c_str(), &content, &content_size);
    return qdb_buffer(_handle, content, content_size);
}

utils::qdb_buffer utils::quasardb_facade::node_topology(const std::string & node_uri) const
{
    const char * content;
    size_t content_size;
    CALL(qdb_node_topology, node_uri.c_str(), &content, &content_size);
    return qdb_buffer(_handle, content, content_size);
}

void utils::quasardb_facade::blob_put(const std::string & alias, const std::string & content)
{
    CALL(qdb_blob_put, alias.c_str(), content.data(), content.size(), 0);
}

void utils::quasardb_facade::blob_update(const std::string & alias, const std::string & content)
{
    CALL(qdb_blob_update, alias.c_str(), content.data(), content.size(), 0);
}

utils::qdb_buffer utils::quasardb_facade::blob_get(const std::string & alias)
{
    const void * result;
    std::size_t result_size;
    CALL(qdb_blob_get, alias.c_str(), &result, &result_size);
    return qdb_buffer(_handle, result, result_size);
}

void utils::quasardb_facade::blob_get_noalloc(const std::string & alias, std::string & content)
{
    std::size_t result_size = content.capacity();
    CALL(qdb_blob_get_noalloc, alias.c_str(), const_cast<char *>(content.data()), &result_size);
    content.resize(result_size);
}

void utils::quasardb_facade::remove(const std::string & alias)
{
    CALL(qdb_remove, alias.c_str());
}

utils::qdb_buffer utils::quasardb_facade::deque_pop_back(const std::string & alias)
{
    const void * result;
    std::size_t result_size;
    CALL(qdb_deque_pop_back, alias.c_str(), &result, &result_size);
    return qdb_buffer(_handle, result, result_size);
}

utils::qdb_buffer utils::quasardb_facade::deque_pop_front(const std::string & alias)
{
    const void * result;
    std::size_t result_size;
    CALL(qdb_deque_pop_front, alias.c_str(), &result, &result_size);
    return qdb_buffer(_handle, result, result_size);
}

void utils::quasardb_facade::deque_push_back(const std::string & alias, const std::string & content)
{
    CALL(qdb_deque_push_back, alias.c_str(), content.data(), content.size());
}

void utils::quasardb_facade::deque_push_front(const std::string & alias,
                                              const std::string & content)
{
    CALL(qdb_deque_push_front, alias.c_str(), content.data(), content.size());
}

std::int64_t utils::quasardb_facade::int_add(const std::string & alias, std::int64_t value)
{
    std::int64_t total;
    CALL(qdb_int_add, alias.c_str(), 1, &total);
    return total;
}

void utils::quasardb_facade::int_put(const std::string & alias, std::int64_t value)
{
    CALL(qdb_int_put, alias.c_str(), value, 0);
}

void utils::quasardb_facade::int_update(const std::string & alias, std::int64_t value)
{
    CALL(qdb_int_update, alias.c_str(), value, 0);
}

std::int64_t utils::quasardb_facade::int_get(const std::string & alias)
{
    std::int64_t value;
    CALL(qdb_int_get, alias.c_str(), &value);
    return value;
}

bool utils::quasardb_facade::hset_contains(const std::string & alias, const std::string & content)
{
    return CALL(qdb_hset_contains, alias.c_str(), content.data(), content.size())
           == qdb_e_element_already_exists;
}

bool utils::quasardb_facade::hset_erase(const std::string & alias, const std::string & content)
{
    return CALL(qdb_hset_contains, alias.c_str(), content.data(), content.size())
           != qdb_e_element_not_found;
}

bool utils::quasardb_facade::hset_insert(const std::string & alias, const std::string & content)
{
    return CALL(qdb_hset_insert, alias.c_str(), content.data(), content.size())
           != qdb_e_element_already_exists;
}

void utils::quasardb_facade::add_tag(const std::string & alias, const std::string & tag)
{
    CALL(qdb_add_tag, alias.c_str(), tag.c_str());
}

qdb_stream_t utils::quasardb_facade::stream_open(const std::string & alias, qdb_stream_mode_t mode)
{
    qdb_stream_t stream;
    CALL(qdb_stream_open, alias.c_str(), mode, &stream);
    return stream;
}

void utils::qdb_stream_facade::close()
{
    CALL(qdb_stream_close);
}

void utils::qdb_stream_facade::write(const std::string & content)
{
    CALL(qdb_stream_write, content.data(), content.size());
}

void utils::quasardb_facade::stream_remove(const std::string & alias)
{
    CALL(qdb_stream_remove, alias.c_str());
}
