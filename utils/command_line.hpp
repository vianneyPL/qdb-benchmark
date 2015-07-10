#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

namespace utils {

class command_line
{
    std::ostringstream _help;
    const char** _begin;
    const char** _end;

public:
    command_line(int argc, const char** argv)
        : _begin(argv), _end(argv+argc)
    {
    }

    std::string help()
    {
        return _help.str();
    }

    bool get_flag(
        const std::string& short_syntax,
        const std::string& long_syntax,
        const std::string& description)
    {
        return find(short_syntax, long_syntax, description) != _end;
    }  

    std::string get_string(
        const std::string& short_syntax,
        const std::string& long_syntax,
        const std::string& description,
        const std::string& default_value)
    {
        auto it = find(short_syntax, long_syntax, description + " (default is " + default_value + ")");
        if (it != _end && ++it != _end)
            return *it;
        else
            return default_value;
    }

    std::vector<int> get_integers(
        const std::string& short_syntax,
        const std::string& long_syntax,
        const std::string& description,
        const std::string& default_value)
    {
        try {        
            std::vector<int> values;        
            std::string list = get_string(short_syntax, long_syntax, description, default_value);

            for_each_token(list, [&](std::string x){ 
                values.push_back(std::stoi(x));
            });

            return values;
        }
        catch (...) {
            throw std::runtime_error("Command line argument " + long_syntax + " is invalid");
        }
    }

private:
    const char** find(
        const std::string& short_syntax,
        const std::string& long_syntax,
        const std::string& description)
    {
        _help
            << "  "
            << std::left
            << std::setw(3)
            << short_syntax
            << std::setw(16)
            << long_syntax 
            << description 
            << std::endl;

        return std::find_if(_begin, _end, 
            [&](const char* arg) { 
                return arg == short_syntax || arg == long_syntax;
            });
    }

    template<typename Function>
    static void for_each_token(const std::string &input, Function fn) 
    {
        int start = 0;

        for(;;)
        {
            int stop = input.find(',', start);
            if (stop == std::string::npos) break;

            fn(input.substr(start,stop));
            start = stop + 1;
        }

        fn(input.substr(start));
    }
};


}