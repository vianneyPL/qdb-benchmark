#include <utils/win32.hpp>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace utils;

std::uint32_t win32::get_last_error()
{
    return GetLastError();
}

std::string win32::get_error_string(std::uint32_t code)
{
    char buffer[256];
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer,
                   sizeof(buffer), NULL);
    return buffer;
}