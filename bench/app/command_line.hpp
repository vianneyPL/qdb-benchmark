#pragma once

#include <bench/app/settings.hpp>
#include <bench/core/test_class.hpp>
#include <string>
#include <vector>

namespace bench
{
namespace app
{

class command_line
{
public:
    command_line(test_class_collection & test_pool, settings & settings) : _test_pool(test_pool), _settings(settings)
    {
    }

    void parse(int argc, const char ** argv);

private:
    test_class_collection & _test_pool;
    settings & _settings;
};

} // namespace app
} // namespace bench
