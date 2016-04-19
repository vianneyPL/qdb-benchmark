#pragma once

#include <bench/core/clock.hpp>
#include <cstdint>

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

    virtual void setup() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;

    std::uint32_t iterations() const
    {
        return _iterations;
    }

protected:
    void add_iteration()
    {
        _iterations++;
    }

private:
    volatile std::uint32_t _iterations;
};

} // namespace bench
