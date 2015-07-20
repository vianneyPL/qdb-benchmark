#pragma once

#include <vector>

namespace utils {

inline std::vector<char> create_random_vector(int size)
{
    return std::vector<char>(size);
}

}