#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

namespace qdb {
namespace bench {
namespace app {

struct command_line_options
{
    bool help;
    bool version;
    std::string cluster_uri;
};

class command_line_parser
{
    std::ostringstream _help;
    command_line_options _options;
    const char** _begin;
    const char** _end;

public:
    command_line_parser(int argc, const char** argv)
     : _begin(argv), _end(argv+argc)
    {
        _help << "Command line options: " << std::endl;
        _options.version = get_flag("-v", "--version", "Display program version and exists");
        _options.help = get_flag("-h", "--help",    "Display program help and exists");
        _options.cluster_uri = get_string("-c", "--cluster", "Set cluster URI", "qdb://127.0.0.1:2836");
    }

    std::string help()
    {
        return _help.str();
    }

    const command_line_options& options()
    {
        return _options;
    }

private:
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
};


}}}