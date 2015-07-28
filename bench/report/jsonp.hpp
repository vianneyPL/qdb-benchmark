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
    jsonp(const std::vector<test_instance> & tests, const std::vector<probe_instance> & probes)
        : _tests(tests), _probes(probes)
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
        clock::time_point stop_time = test.result.back().time;

        _file << "{"
              << "\"name\":\"" << test.tclass.name << "\","
              << "\"description\":\"" << test.tclass.description << "\","
              << "\"content_size\":" << test.config.content_size << ","
              << "\"threads\":";

        write_time_series(test.result, test.start_time, stop_time);

        for (auto & probe : _probes)
        {
            _file << ",\"" << probe.pclass.name << "\":";
            write_time_series(probe.result, test.start_time, stop_time);
        }

        _file << "}";
    }

    template <typename T>
    void write_time_series(const time_series<T> & samples,
                           clock::time_point start_time,
                           clock::time_point stop_time)
    {
        _file << "[";

        bool need_comma = false;
        for (sample<unsigned long> sample : samples)
        {
            if (sample.time < start_time) continue;
            if (sample.time > stop_time) continue;
            if (need_comma) _file << ",";

            _file << "[" << get_elapsed_millis(start_time, sample.time);

            for (unsigned long value : sample.values)
            {
                _file << "," << value;
            }

            _file << "]";
            need_comma = true;
        }
        _file << "]";
    }

    long long get_elapsed_millis(clock::time_point from, clock::time_point to)
    {
        clock::duration elapsed = to - from;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    std::ofstream _file;
    const std::vector<test_instance> & _tests;
    const std::vector<probe_instance> & _probes;
};
}
}
