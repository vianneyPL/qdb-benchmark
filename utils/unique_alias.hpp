#pragma once

#include <string>

namespace utils
{
class unique_alias
{
public:
    unique_alias();

    void set_watermark(unsigned long iteration);

    operator const std::string &() const
    {
        return _string;
    }

private:
    std::string _string;
};
}