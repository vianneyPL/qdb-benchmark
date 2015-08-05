#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace utils
{
template <typename T, typename F>
inline void for_each(std::vector<std::unique_ptr<T>> & collection, F fn)
{
    for (auto & element : collection)
        std::mem_fun_ref(fn)(*element);
}
}