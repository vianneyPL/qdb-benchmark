#include <snmp/storage.hpp>

using namespace snmp;

std::vector<snmp::storage> snmp::storage::discover(session & session)
{
    std::vector<snmp::storage> results;

    // enumerate stoage types
    std::map<oid, variant> variables = session.walk({1, 3, 6, 1, 2, 1, 25, 2, 3, 1});

    for (auto & var : variables)
    {
        // we're only interested in indexes
        if (!var.first.starts_with({1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 1})) continue;

        results.push_back(snmp::storage(variables, var.second));
    }

    return results;
}

snmp::storage::storage(std::map<oid, variant> & variables, oid::subid_type index)
{
    _type = get_type(variables[{1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 2, index}]);
    _name = static_cast<const char *>(variables[{1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 3, index}]);
    _allocation_unit = variables[{1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 4, index}];
    _size = variables[{1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 5, index}];

    _used_space_oid = {1, 3, 6, 1, 2, 1, 25, 2, 3, 1, 6, index};
    _used_space = variables[_used_space_oid];
}

void snmp::storage::update(const std::map<oid, variant> & variables)
{
    _used_space = variables.at(_used_space_oid);
}

storage_type snmp::storage::get_type(const oid & type_oid)
{
    static std::map<snmp::oid, snmp::storage_type> mapping = {
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 1}, storage_type::other},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 2}, storage_type::ram},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 3}, storage_type::virtual_memory},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 4}, storage_type::fixed_disk},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 5}, storage_type::removable_disk},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 6}, storage_type::floppy_disk},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 7}, storage_type::compact_disk},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 8}, storage_type::ram_disk},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 9}, storage_type::flash_memory},
        {{1, 3, 6, 1, 2, 1, 25, 2, 1, 10}, storage_type::network_disk}};

    return mapping[type_oid];
}

std::ostream & snmp::operator<<(std::ostream & s, snmp::storage_type t)
{
    switch (t)
    {
    case storage_type::other:
        s << "Other";
        break;
    case storage_type::ram:
        s << "RAM";
        break;
    case storage_type::virtual_memory:
        s << "Virtual Memory";
        break;
    case storage_type::fixed_disk:
        s << "Fixed Disk";
        break;
    case storage_type::removable_disk:
        s << "Removable Disk";
        break;
    case storage_type::floppy_disk:
        s << "Floppy Disk";
        break;
    case storage_type::compact_disk:
        s << "Compact Disk";
        break;
    case storage_type::ram_disk:
        s << "RAM Disk";
        break;
    case storage_type::flash_memory:
        s << "Flash Memory";
        break;
    case storage_type::network_disk:
        s << "Network Disk";
        break;
    default:
        s << "???";
    }
    return s;
}
