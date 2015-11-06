#pragma once

#include <utils/unique_alias.hpp>

namespace utils
{
class unique_alias_provider
{
public:
    const std::string & alias(unsigned long iteration) const
    {
        _alias.set_watermark(iteration);
        return _alias;
    }

private:
    mutable utils::unique_alias _alias;
};
}