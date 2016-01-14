#include <utils/unique_alias.hpp>
#include <utils/watermark.hpp>

#include <cppformat/format.h>
#include <atomic>
#include <chrono>

static std::atomic<int> __counter(0);

static const char __base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

utils::unique_alias::unique_alias()
{
    using namespace std::chrono;
    auto t = duration_cast<seconds>(steady_clock::now().time_since_epoch()).count();
    auto n = __counter++;

    _string = fmt::format("benchmarks-{}-{}-AAAAAA", t, n);
}

void utils::unique_alias::set_watermark(unsigned long iteration)
{
    utils::watermark::replace_end(_string, iteration);
}
