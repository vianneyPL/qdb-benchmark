#pragma once

#include "test.hpp"
#include "size.hpp"

#include <string>

namespace qdb {
namespace benchmark {
namespace tests {

class blob_get : public qdb::benchmark::framework::test
{
public:
    blob_get(qdb::benchmark::size size) : _size(size)
    {

    }

    std::string id() const override
    {
        return "blob_get_" + _size.short_string();
    }

    std::string description() const override
    {
        return "Perform a qdb_get() on the same entry of size " + _size.long_string();
    }

    void init(qdb_handle_t h) const override
    {
        std::vector<char> content(_size.bytes());
        qdb_put(h, "alias", content.data(), content.size(), 0);
    }

    void run(qdb_handle_t h) const override
    {
        const char* content;
        std::size_t content_size;
        qdb_get(h, "alias", &content, &content_size);        
        qdb_free_buffer(h, content);
    }

    void cleanup(qdb_handle_t h) const override
    {        
        qdb_remove(h, "alias");
    }

private:
    qdb::benchmark::size _size;
};

}}}