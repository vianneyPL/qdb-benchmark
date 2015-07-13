#pragma once

#include <bench/core/time_series.hpp>

#include <chrono>

namespace bench {
namespace framework {

class chronometer
{
    using clock = std::chrono::high_resolution_clock;

public:
    chronometer()
        : _period(std::chrono::milliseconds(200))
    {        
    }

    void start()
    {
        _start_time = _previous_time = clock::now();
        _iterations = 0;
    }

    void step()
    {
        _iterations++;

        clock::time_point now = clock::now();

        if (is_time_to_save(now))
            save(now);
    }

    void stop()
    {
        save(clock::now());
    }

    const time_series data() const
    {
        return _data;
    }

private:

    bool is_time_to_save(clock::time_point now) const
    {
        return now - _previous_time >= _period;
    }

    void save(clock::time_point now)
    {
        _data.add(now, _iterations);
        _previous_time = now;
    }

    const clock::duration _period;
    time_series _data;
    unsigned long _iterations;
    clock::time_point _start_time, _previous_time;
};

}}