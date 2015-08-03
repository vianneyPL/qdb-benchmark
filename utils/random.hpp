#pragma once

#include <algorithm>
#include <random>
#include <vector>

namespace utils
{
inline std::vector<char> create_random_vector(int size)
{
    return std::vector<char>(size);
}

inline char get_random_char()
{
    const char charset[] = "0123456789"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "abcdefghijklmnopqrstuvwxyz";

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, sizeof(charset) - 1);

    return charset[distribution(generator)];
}

inline std::string create_random_string(int size)
{
    std::string str(size, 0);
    std::generate_n(str.begin(), size, get_random_char);
    return str;
}
}
