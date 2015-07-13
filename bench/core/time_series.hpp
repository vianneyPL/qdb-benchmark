#pragma once

#include <chrono>
#include <map>

namespace bench {

class time_series 
{   
public:
    using clock = std::chrono::high_resolution_clock;
    using iterator = std::map<clock::time_point, unsigned long>::const_iterator;

    void add(clock::time_point time, unsigned long value)
    {
        _samples.emplace(time, value);
    }

    iterator begin() const { return _samples.begin(); }
    iterator end() const { return _samples.end(); }

    double average() const
    {
        auto first = _samples.begin(); 
        auto last = _samples.rbegin();
        unsigned long iterations = last->second - first->second;
        std::chrono::duration<double> elapsed = last->first - first->first;

        return iterations / elapsed.count();
    }

private:
    std::map<clock::time_point, unsigned long> _samples;
};

}