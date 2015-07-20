#pragma once

namespace bench {

class test_runner 
{
public:
    virtual void run() = 0;
    virtual ~test_runner() {};
};
}