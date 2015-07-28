#pragma once

#include <qdb/client.h>

#include <string>

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
    qdb_buffer(qdb_buffer && other)
        : qdb_buffer()
    {
        std::swap(_handle, other._handle);
        std::swap(_content, other._content);
        std::swap(_content_size, other._content_size);
    }

    ~qdb_buffer()
    {
        if (_content)
            qdb_free_buffer(_handle, _content);
    }

    const char * data() const
    {
        return _content;
    }

private:
    qdb_handle_t _handle;
    const char * _content;
    size_t _content_size;
};

class qdb_wrapper
{
public:
    qdb_wrapper()
    {
        _handle = qdb_open_tcp();
    }

    ~qdb_wrapper()
    {
        call(qdb_close);
    }

    void connect(const std::string & cluster_uri)
    {
        call(qdb_connect, cluster_uri.c_str());
    }

    void free_buffer(const char * buffer)
    {
        qdb_free_buffer(_handle, buffer);
    }

    qdb_buffer node_status(const std::string & node_uri)
    {
        const char * content;
        size_t content_size;
        call(qdb_node_status, node_uri.c_str(), &content, &content_size);
        return qdb_buffer(_handle, content, content_size);
    }

    template <typename Function, typename... Args>
    qdb_error_t call(Function function, Args... args) const
    {
        qdb_error_t error = function(_handle, args...);
        throw_if_error(error);
        return error;
    }

private:
    void throw_if_error(qdb_error_t err) const
    {
        if (!err)
            return;

        throw std::runtime_error(qdb_error(err));
    }

    qdb_handle_t _handle;
};
}
