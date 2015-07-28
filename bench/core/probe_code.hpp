#pragma once

namespace bench
{
typedef unsigned long probe_sample;
class probe_code
{
public:
    virtual probe_sample read() = 0;
};
}
