#pragma once

#include <bench/core/time_series.hpp>

#include <chrono>

namespace bench {
namespace framework {

class time_sampler
{
    using clock = std::chrono::high_resolution_clock;

public:
    time_sampler(time_series& results)
        : _results(results), _iterations(0), _period(std::chrono::milliseconds(200))
    {        
    }

    void sample()
    {
        updateState();
        if (isTimeToSaveState())
            saveState();
    }

private:
    void updateState()
    {
        _iterations++;
        _now = clock::now();
    }

    bool isTimeToSaveState() const
    {
        return _now - _lastSave >= _period;
    }

    void saveState()
    {
        _results.add(_now, _iterations);
        _lastSave = _now;
    }

    const clock::duration _period;
    time_series& _results;
    unsigned long _iterations;
    clock::time_point _now, _lastSave;
};

}}