#include <bench/report/jsonp.hpp>

#define ARDUINOJSON_ENABLE_STD_STREAM
#include <ArduinoJson.h>

#include <algorithm>
#include <fstream>
#include <sstream>

static const char * unit_name(bench::unit unit)
{
    switch (unit)
    {
    case bench::unit::none:
        return "none";
    case bench::unit::bytes:
        return "bytes";
    case bench::unit::bytes_per_second:
        return "bytes/second";
    default:
        return "undefined";
    }
}

static long long get_elapsed_millis(bench::time_point from, bench::time_point to)
{
    bench::duration elapsed = to - from;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
}

template <typename Iterator>
static void write_errors(JsonArray & jsonArray, Iterator begin, Iterator end)
{
    for (Iterator it = begin; it != end; ++it)
    {
        JsonObject & error = jsonArray.createNestedObject();
        error["message"] = it->message.c_str();
        error["details"] = it->details.c_str();
    }
}

static void
write_samples(JsonArray & jsonArray, const std::vector<bench::sample> & samples, bench::time_point start_time)
{
    for (auto & sample : samples)
    {
        JsonArray & nestedArray = jsonArray.createNestedArray();
        nestedArray.add(get_elapsed_millis(start_time, sample.time));

        for (auto value : sample.values)
            nestedArray.add(value);
    }
}

template <typename Iterator>
static void write_series(JsonObject & jsonObject, Iterator begin, Iterator end, bench::time_point start_time)
{
    for (Iterator it = begin; it != end; ++it)
    {
        JsonObject & serie = jsonObject.createNestedObject(it->first.c_str());
        serie["name"] = it->second.name.c_str();
        serie["unit"] = unit_name(it->second.unit);
        write_samples(serie.createNestedArray("samples"), it->second.samples, start_time);
    }
}

void bench::report::jsonp::add_test(const bench::test_instance & test)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject & root = jsonBuffer.createObject();

    root["name"] = test.tclass.name.c_str();
    root["description"] = test.tclass.description.c_str();
    root["content_size"] = test.config.content_size;
    root["thread_count"] = test.config.thread_count;

    write_errors(root.createNestedArray("errors"), test.errors.begin(), test.errors.end());
    write_series(root.createNestedObject("series"), test.result.begin(), test.result.end(), test.start_time);

    _file << "addTestResult(" << root << ");" << std::endl;
}
