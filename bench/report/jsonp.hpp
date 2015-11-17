#pragma once

#include <bench/core/test_instance.hpp>

#include <algorithm>
#include <fstream>
#include <sstream>

namespace bench
{
namespace report
{

class jsonp
{
public:
    jsonp()
    {
        _file.open("results.jsonp");
    }

    ~jsonp()
    {
        _file.close();
    }

    void add_test(const test_instance & test)
    {
        _file << "addTestResult({"
              << "\"name\":\"" << test.tclass.name << "\","
              << "\"description\":\"" << test.tclass.description << "\","
              << "\"content_size\":" << test.config.content_size << ","
              << "\"thread_count\":" << test.config.thread_count;

        if (!test.error.empty())
        {
            _file << ",\"error\":\"" << test.error << "\"";
        }

        _file << ",\"series\":";
        write_time_series(test.result, test.start_time);
        _file << "});" << std::endl;
    }

private:
    void write_time_series(const time_series_collection & series, time_point start_time)
    {
        _file << "{";

        bool need_comma = false;
        for (auto & serie : series)
        {
            if (need_comma) _file << ",";

            _file << "\"" << serie.first << "\":{"
                  << "\"name\":\"" << serie.second.name << "\","
                  << "\"unit\":\"" << unit_name(serie.second.unit) << "\","
                  << "\"samples\":";

            write_samples(serie.second.samples, start_time);

            _file << "}";
            need_comma = true;
        }
        _file << "}";
    }

    void write_samples(const std::vector<bench::sample> & samples, time_point start_time)
    {
        _file << "[";

        bool need_comma = false;
        for (auto & sample : samples)
        {
            if (need_comma) _file << ",";

            _file << "[" << get_elapsed_millis(start_time, sample.time);

            for (auto value : sample.values)
            {
                _file << "," << value;
            }

            _file << "]";
            need_comma = true;
        }
        _file << "]";
    }

    long long get_elapsed_millis(time_point from, time_point to)
    {
        duration elapsed = to - from;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

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

    std::ofstream _file;
};
}
}
