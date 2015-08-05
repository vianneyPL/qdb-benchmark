#pragma once

namespace bench
{
class test_code
{
public:
    virtual void setup() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;

    virtual ~test_code()
    {
    }
};
}
