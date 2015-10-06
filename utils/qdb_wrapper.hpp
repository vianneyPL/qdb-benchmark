#pragma once

#include <qdb/client.h>

#include <string>
#include <stdexcept>
#include <cstdint>

namespace utils
{
class qdb_buffer
{
public:
    qdb_buffer() : _handle(nullptr), _content(nullptr), _content_size(0)
    {
    }

    qdb_buffer(qdb_handle_t h, const char * content, size_t content_size)
        : _handle(h), _content(content), _content_size(content_size)
    {
    }

    qdb_buffer(const qdb_buffer &) = delete;
    qdb_buffer(qdb_buffer && other) : qdb_buffer()
    {
        std::swap(_handle, other._handle);
        std::swap(_content, other._content);
        std::swap(_content_size, other._content_size);
    }

    ~qdb_buffer()
    {
        if (_content) qdb_free_buffer(_handle, _content);
    }

    const char * data() const
    {
        return _content;
    }

    size_t size() const
    {
        return _content_size;
    }

private:
    qdb_handle_t _handle;
    const char * _content;
    size_t _content_size;
};

class qdb_wrapper
{
public:
    qdb_wrapper();
    ~qdb_wrapper();

    void connect(const std::string & cluster_uri);
    qdb_buffer node_status(const std::string & node_uri) const;
    qdb_buffer node_topology(const std::string & node_uri) const;
    void free_buffer(const char * buffer);

    void remove(const std::string & alias);

    void blob_put(const std::string & alias, const std::string & content);
    void blob_update(const std::string & alias, const std::string & content);
    qdb_buffer blob_get(const std::string & alias);
    void blob_get_noalloc(const std::string & alias, std::string & content);

    qdb_buffer deque_pop_back(const std::string & alias);
    qdb_buffer deque_pop_front(const std::string & alias);
    void deque_push_back(const std::string & alias, const std::string & content);
    void deque_push_front(const std::string & alias, const std::string & content);

    std::int64_t int_add(const std::string & alias, std::int64_t value);
    void int_put(const std::string & alias, std::int64_t value);
    void int_update(const std::string & alias, std::int64_t value);
    std::int64_t int_get(const std::string & alias);

private:
    bool is_error(qdb_error_t err) const
    {
        return err != qdb_e_ok;
    }

    template <typename Function, typename... Args>
    qdb_error_t call(std::string name, Function function, Args... args) const
    {
        qdb_error_t err = function(_handle, args...);
        if (is_error(err)) throw std::runtime_error(name + ": " + qdb_error(err));
        return err;
    }

    qdb_handle_t _handle;
};
}
