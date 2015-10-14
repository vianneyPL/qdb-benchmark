#pragma once

#include <string>

namespace bench
{
namespace tests
{
namespace qdb
{
class alias
{
public:
    alias();

    void set_watermark(unsigned long iteration);

    operator const std::string &() const
    {
        return _string;
    }

private:
    std::string _string;
};
}
}
}