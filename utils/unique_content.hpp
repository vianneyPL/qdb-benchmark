#pragma once

#include <string>

namespace utils
{
class unique_content
{
public:
    unique_content(std::size_t size);

    void set_watermark(unsigned long iteration);

    operator const std::string &() const
    {
        return _string;
    }

private:
    std::string _string;
};
}