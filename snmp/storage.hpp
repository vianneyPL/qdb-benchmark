#pragma once

#include <snmp/session.hpp>

#include <ostream>
#include <map>
#include <vector>

namespace snmp
{
enum class storage_type
{
    other,
    ram,
    virtual_memory,
    fixed_disk,
    removable_disk,
    floppy_disk,
    compact_disk,
    ram_disk,
    flash_memory,
    network_disk
};

class storage
{
public:
    static std::vector<storage> discover(session &);

    void set_useful_variables(std::map<oid, variant> & variables) const
    {
        variables.emplace(_used_space_oid, variant());
    }

    void update(const std::map<oid, variant> & variables);

    const std::string & name() const
    {
        return _name;
    }

    long allocation_unit() const
    {
        return _allocation_unit;
    }

    long used_space() const
    {
        return _used_space;
    }

    long size() const
    {
        return _size;
    }

    storage_type type() const
    {
        return _type;
    }

    std::vector<snmp::oid> oids() const
    {
        return {_used_space_oid};
    }

private:
    storage(std::map<oid, variant> & variables, oid::subid_type index);

    static storage_type get_type(const oid & oid);

    storage_type _type;
    std::string _name;
    long _allocation_unit;
    long _size;
    unsigned long _used_space;
    oid _used_space_oid;
};

std::ostream & operator<<(std::ostream & s, storage_type t);
}
