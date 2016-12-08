#include <utils/watermark.hpp>

static const char __base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const size_t base64_length = 64;
static_assert(sizeof(__base64) == base64_length + 1 /* trailing zero */, "wrong chain length");

void utils::watermark::replace_end(std::string & s, unsigned long id)
{
    size_t index = s.size();
    for (auto digit = 0u; digit < watermark::length && index > 0; ++digit)
    {
        s[--index] = __base64[id % base64_length];
        id /= base64_length;
    }
}

void utils::watermark::replace_front(std::string & s, unsigned long id)
{
    if (s.size() < length)
    {
        replace_end(s, id);
        return;
    }

    for (int digit = watermark::length; digit >= 0; --digit)
    {
        s[digit] = __base64[id % base64_length];
        id /= base64_length;
    }
}
