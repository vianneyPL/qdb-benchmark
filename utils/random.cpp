#include <utils/random.hpp>

#include <algorithm>
#include <random>

static std::default_random_engine __generator;

static char get_random_char()
{
    static const char charset[] = "0123456789"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "abcdefghijklmnopqrstuvwxyz";
    static std::uniform_int_distribution<int> distribution(0, sizeof(charset) - 2);

    return charset[distribution(__generator)];
}

std::string utils::create_random_string(size_t size)
{
    std::string str(size, 0);
    for (size_t i = 0; i < size; i++)
        str[i] = get_random_char();
    return str;
}

std::string utils::get_temporary_filename()
{
    return create_random_string(16) + ".tmp";
}
