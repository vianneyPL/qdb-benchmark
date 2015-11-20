#pragma once

#include <cppformat/format.h>

#include <string>
#include <vector>

namespace utils
{
template <typename Arg>
std::string get_argument_string(Arg * arg)
{
    return fmt::format("{}", static_cast<const void *>(arg));
}

template <typename Arg>
std::string get_argument_string(const Arg & arg)
{
    return fmt::format("{}", arg);
}

std::string get_argument_string(const char * arg)
{
    return fmt::format("\"{}\"", arg);
}

template <typename... Args>
std::string make_invocation_string(const char * function_name, Args &&... args)
{
    std::string result = function_name;
    result.push_back('(');
    for (std::string arg : {get_argument_string(std::forward<Args>(args))...})
        result += arg + ", ";
    result.pop_back();
    result.back() = ')';
    return result;
}
}