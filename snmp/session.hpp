#pragma once

#include <snmp/oid.hpp>
#include <snmp/variant.hpp>

#include <map>

namespace snmp
{
class session
{
public:
    void open(const std::string & peername, const std::string & community);
    void close();
    std::map<oid, variant> walk(oid);
    void get_bulk(std::map<oid, variant> & variables);

private:
    void * _ss;
    static bool _initialized;
};
}
