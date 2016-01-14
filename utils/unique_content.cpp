#include <utils/unique_content.hpp>

#include <utils/random.hpp>
#include <utils/watermark.hpp>

utils::unique_content::unique_content(std::size_t size)
{
    _string = utils::create_random_string(size);
}

void utils::unique_content::set_watermark(unsigned long iteration)
{
    utils::watermark::replace_front(_string, iteration);
}
