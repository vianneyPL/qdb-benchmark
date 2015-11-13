#pragma once

#include <cstdint>
#include <initializer_list>
#include <vector>
#include <ostream>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
// This is sad but I need the size of ::oid
// There is no other portable way to do this.
// Sorry.
// --Benoit

namespace snmp
{
class oid
{
public:
    typedef ::oid subid_type;

    oid()
    {
    }

    oid(const subid_type * ids, std::size_t length) : _ids(ids, ids + length)
    {
    }

    oid(std::initializer_list<subid_type> args) : _ids(args)
    {
    }

    bool operator<(const oid & other) const
    {
        return _ids < other._ids;
    }

    bool starts_with(const oid & other) const
    {
        return starts_with(_ids, other._ids);
    }

    const subid_type * data() const
    {
        return _ids.data();
    }

    std::size_t size() const
    {
        return _ids.size();
    }

private:
    std::vector<subid_type> _ids;

    //  static int compare(const std::vector<subid_type> & lhs, const std::vector<subid_type> &
    //  rhs);
    static bool starts_with(const std::vector<subid_type> & lhs,
                            const std::vector<subid_type> & rhs);
    //  static bool equals(const std::vector<subid_type> & lhs, const std::vector<subid_type> &
    //  rhs);
};

bool operator==(const oid & lhs, const oid & rhs);
std::ostream & operator<<(std::ostream &, const oid & oid);
}
