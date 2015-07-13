#pragma once

#include <bench/core/time_series.h>

#include <chrono>

namespace bench {
namespace framework {

class time_sampler
{
    const std::chrono::duration _period;    
    time_series _samples;
    unsigned long _iterations;
    std::chrono::time_point _now, _lastSave;

public:
    time_sampler()
        : _iterations(0), _period(std::chrono::seconds(1))
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
        _now = std::chrono::high_resolution_clock::now();
    }

    bool isTimeToSaveSnapshot() const
    {
        return _now - _lastSave >= _period;
    }

    void saveState()
    {
        _samples.add(_now, _iterations);
        _lastSave = _now;
    }
};

}}