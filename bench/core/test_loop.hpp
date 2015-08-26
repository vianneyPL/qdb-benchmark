#pragma once

#include <bench/core/clock.hpp>

namespace bench
{
class test_loop
{
public:
    test_loop() : _iterations(0)
    {
    }

    virtual ~test_loop()
    {
    }

    virtual void run(time_point timeout) = 0;

    unsigned long iterations() const
    {
        return _iterations;
    }

protected:
    void add_iteration()
    {
        _iterations++;
    }

private:
    volatile unsigned long _iterations;
};
}
