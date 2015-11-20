#pragma once

#include <stdexcept>
#include <string>

namespace utils
{
class detailed_error : public std::exception
{
public:
    detailed_error(std::string message, std::string invocation) : _message(message), _invocation(invocation)
    {
    }

    const char * what() const throw()
    {
        return _message.c_str();
    }

    const std::string & message() const
    {
        return _message;
    }

    const std::string & invocation() const
    {
        return _invocation;
    }

private:
    std::string _message, _invocation;
};
}
