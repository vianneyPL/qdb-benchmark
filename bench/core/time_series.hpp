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
        _samples[time] += value;
    }

    iterator begin() const { return _samples.begin(); }
    iterator end() const { return _samples.end(); }

    double average() const
    {
        return total() / duration().count();
    }

    unsigned total() const
    {
        unsigned long n = 0;
        for (auto sample : _samples)
        {
            n += sample.second;        
        }
        return n;
    }

    std::chrono::duration<double> duration() const
    {
        auto first = _samples.begin(); 
        auto last = _samples.rbegin();
        return last->first - first->first;
    }

    template<typename Collection>
    static time_series sum(Collection sources)
    {
        time_series result;
        for (const time_series& source : sources)
        {
            for (auto sample : source._samples)
            {
                result.add(sample.first, sample.second);
            }     
        }    

        return result;    
    }

private:
    std::map<clock::time_point, unsigned long> _samples;
};

}