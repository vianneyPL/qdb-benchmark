#pragma once

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <stdexcept>

namespace snmp
{
class protocol_error : public std::exception
{
public:
    protocol_error(long errstat)
    {
        snprintf(message, sizeof(message), "SNMP protocol error: %s", snmp_errstring(errstat));
    }

    const char * what() const throw() override
    {
        return message;
    }

private:
    char message[256];
};

class session_error : public std::exception
{
public:
    session_error(snmp_session * psess)
    {
        char * str;
        snmp_error(psess, NULL, NULL, &str);
        snprintf(message, sizeof(message), "SNMP session error: %s", str);
        free(str);
    }

    const char * what() const throw() override
    {
        return message;
    }

private:
    char message[256];
};
}
