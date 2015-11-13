#include <snmp/oid.hpp>

bool snmp::oid::starts_with(const std::vector<subid_type> & lhs,
                            const std::vector<subid_type> & rhs)
{
    return snmp_oidtree_compare(lhs.data(), lhs.size(), rhs.data(), rhs.size()) == 0;
}

bool snmp::operator==(const snmp::oid & lhs, const snmp::oid & rhs)
{
    return snmp_oid_compare(lhs.data(), lhs.size(), rhs.data(), rhs.size()) == 0;
}

std::ostream & snmp::operator<<(std::ostream & s, const snmp::oid & oid)
{
    for (size_t i = 0; i < oid.size(); i++)
    {
        if (i > 0) s << '.';
        s << oid.data()[i];
    }
    return s;
}
