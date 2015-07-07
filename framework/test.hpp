#pragma once

#include <qdb/client.h>

namespace qdb {
namespace benchmark {
namespace framework {

class test
{
public:
    virtual void init(qdb_handle_t) const;
    virtual void cleanup(qdb_handle_t) const;
    virtual void run(qdb_handle_t) const;
};

}}}