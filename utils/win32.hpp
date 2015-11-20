#pragma once

#include <cstdint>
#include <string>

namespace utils
{
namespace win32
{
std::uint32_t get_last_error();
std::string get_error_string(std::uint32_t);
}
}