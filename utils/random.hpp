#pragma once

#include <algorithm>
#include <random>
#include <vector>

namespace utils
{
inline std::string create_random_string(size_t size)
{
    static const char charset[] = "0123456789"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "abcdefghijklmnopqrstuvwxyz";
    static std::uniform_int_distribution<int> distribution(0, sizeof(charset) - 1);

    std::default_random_engine generator;

    std::string str(size, 0);
    for (size_t i = 0; i < size; i++)
        str[i] = charset[distribution(generator)];

    return str;
}
}
