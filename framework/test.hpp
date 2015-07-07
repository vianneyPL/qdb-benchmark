#pragma once

#include <qdb/client.h>
#include <string>

namespace qdb {
namespace benchmark {
namespace framework {

class test
{
public:
    virtual void init(qdb_handle_t) const = 0;
    virtual void run(qdb_handle_t) const = 0;
    virtual void cleanup(qdb_handle_t) const = 0;
    
    virtual std::string id() const = 0;
    virtual std::string description() const = 0;
};

}}}