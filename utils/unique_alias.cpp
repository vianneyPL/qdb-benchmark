#include <utils/unique_alias.hpp>

#include <atomic>
#include <chrono>
#include <sstream>

static std::atomic<int> __counter(0);

static const char __base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

utils::unique_alias::unique_alias()
{
    std::ostringstream s;

    s << "benchmarks-"
      << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count()
      << "-" << __counter++ << "-AAAAAA"; // reserve 6 chars for the watermark

    _string = s.str();
}

void utils::unique_alias::set_watermark(unsigned long iteration)
{
    size_t index = _string.size();
    for (int digit = 0; digit < 6; digit++)
    {
        _string[--index] = __base64[iteration & 63];
        iteration /= 64;
    }
}
