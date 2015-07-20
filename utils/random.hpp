#pragma once

#include <algorithm>
#include <vector>

namespace utils {

inline std::vector<char> create_random_vector(int size)
{
    return std::vector<char>(size);
}

inline char get_random_char()
{
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[rand()%max_index]; 
}

inline std::string create_random_string(int size)
{
    std::string str(size, 0);
    std::generate_n( str.begin(), size, get_random_char);
    return str;
}

}