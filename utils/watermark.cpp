#include <utils/watermark.hpp>

static const char __base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void utils::watermark::replace_end(std::string & s, unsigned long id)
{
    size_t index = s.size();
    for (std::size_t digit = 0; digit < watermark::length && index>0; digit++)
    {
        s[--index] = __base64[id & 63];
        id /= 64;
    }
}

void utils::watermark::replace_front(std::string & s, unsigned long id)
{
    if (s.size() < length)
    {
        replace_end(s, id);
        return;
    }

    for (int digit = watermark::length; digit >= 0; digit--)
    {
        s[digit] = __base64[id & 63];
        id /= 64;
    }
}
