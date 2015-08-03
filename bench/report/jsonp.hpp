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
    jsonp(const std::vector<test_instance> & tests) : _tests(tests)
    {
    }

    void save()
    {
        _file.open("results.jsonp");
        _file << "results=[";
        for (unsigned i = 0; i < _tests.size(); i++)
        {
            if (i > 0) _file << ",";
            write_test(_tests[i]);
        }
        _file << "]";
        _file.close();
    }

private:
    void write_test(const test_instance & test)
    {
        _file << "{"
              << "\"name\":\"" << test.tclass.name << "\","
              << "\"description\":\"" << test.tclass.description << "\","
              << "\"content_size\":" << test.config.content_size << ","
              << "\"thread_count\":" << test.config.thread_count;

        for (auto & kvp : test.result)
        {
            // if (need_comma)
            _file << ",";
            _file << "\"" << kvp.first << "\":";
            write_time_series(kvp.second, test.start_time);
        }

        _file << "}";
    }

    void write_time_series(const time_series & samples, time_point start_time)
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

    std::ofstream _file;
    const std::vector<test_instance> & _tests;
};
}
}
