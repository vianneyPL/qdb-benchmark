#pragma once

namespace bench {

class time_series {
    std::map<std::chrono::time_point, unsigned long> _samples;
public:

    void add(std::chrono::time_point time, unsigned long value)
    {
        _samples.insert(time, value);
    }
};

}