#pragma once

#include <string>
#include <cstdint>

namespace qdb {
namespace benchmark {
 
class size
{
public:
    size(std::size_t bytes)
        : _bytes(bytes)
    {

    }

    std::string short_string() const
    {
        if (_bytes >= MEGA)
            return std::to_string(_bytes/MEGA) + "mb";
        if (_bytes >= KILO)
            return std::to_string(_bytes/KILO) + "k";
        return std::to_string(_bytes);
    }

    std::string long_string() const
    {
        if (_bytes >= MEGA)
            return std::to_string(_bytes/MEGA) + " mega-bytes";
        if (_bytes >= KILO)
            return std::to_string(_bytes/KILO) + " kilo-bytes";
        return std::to_string(_bytes) + " bytes";
    }

    std::size_t bytes() const 
    {
        return _bytes;
    }

private:
    std::size_t _bytes;

    const static std::size_t MEGA = 1<<20;
    const static std::size_t KILO = 1<<10;
};

}}