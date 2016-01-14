#pragma once

#include <utils/unique_content.hpp>

namespace utils
{
class unique_content_provider
{
public:
    unique_content_provider(std::size_t size) : _content(size)
    {
    }

    const std::string & content(unsigned long iteration) const
    {
        _content.set_watermark(iteration);
        return _content;
    }

private:
    mutable utils::unique_content _content;
};
}