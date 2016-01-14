#pragma once

#include <string>

namespace utils
{
namespace watermark
{
const size_t length = 6;
void replace_end(std::string & s, unsigned long id);
void replace_front(std::string & s, unsigned long id);
}
}