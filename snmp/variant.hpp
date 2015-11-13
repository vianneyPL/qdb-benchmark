#pragma once

#include <snmp/oid.hpp>

#include <string>

namespace snmp
{
class variant
{
public:
    variant() : _type(undefined_type)
    {
    }

    variant & operator=(std::string s)
    {
        _type = string_type;
        _string_value = s;
        return *this;
    }

    variant & operator=(long i)
    {
        _type = integer_type;
        _integer_value = i;
        return *this;
    }

    variant & operator=(const oid & o)
    {
        _type = oid_type;
        _oid_value = o;
        return *this;
    }

    operator int() const
    {
        return _type == integer_type ? _integer_value : 0;
    }

    operator const char *() const
    {
        return _type == string_type ? _string_value.c_str() : "";
    }

    operator oid() const
    {
        return _type == oid_type ? _oid_value : oid();
    }

private:
    enum
    {
        undefined_type,
        string_type,
        integer_type,
        oid_type
    } _type;
    std::string _string_value;
    long _integer_value;
    oid _oid_value;
};
}
