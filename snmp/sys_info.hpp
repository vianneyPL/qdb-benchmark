#pragma once

#include <snmp/storage.hpp>

#include <string>
#include <vector>

namespace snmp
{
class sys_info
{
public:
    struct physical_memory;
    struct virtual_memory;
    struct cached_memory;
    struct swap_space;
    struct fixed_disks;

    sys_info(std::string peername) : _peername(peername)
    {
    }

    void connect()
    {
        _session.open(_peername, "public");
        _storages = snmp::storage::discover(_session);

        _physical_memory = nullptr;
        _virtual_memory = nullptr;
        _cached_memory = nullptr;
        _swap_space = nullptr;
        _fixed_disks.clear();

        for (auto & storage : _storages)
        {
            if (storage.name() == "Physical memory") _physical_memory = &storage;
            if (storage.name() == "Virtual memory") _virtual_memory = &storage;
            if (storage.name() == "Cached memory") _cached_memory = &storage;
            if (storage.name() == "Swap space") _swap_space = &storage;
            if (storage.type() == storage_type::fixed_disk) _fixed_disks.push_back(&storage);

            for (auto oid : storage.oids())
            {
                _variables.emplace(oid, variant());
            }
        }
    }

    void update()
    {
        _session.get_bulk(_variables);

        for (auto & storage : _storages)
        {
            storage.update(_variables);
        }
    }

    void close()
    {
        _session.close();
    }

    template <typename InformationType>
    bool supports() const;

    template <typename InformationType>
    std::int64_t get() const;

    const std::vector<snmp::storage> & storages() const
    {
        return _storages;
    }

private:
    std::string _peername;
    snmp::session _session;
    std::vector<snmp::storage> _storages;
    std::map<snmp::oid, snmp::variant> _variables;
    const snmp::storage * _physical_memory;
    const snmp::storage * _virtual_memory;
    const snmp::storage * _cached_memory;
    const snmp::storage * _swap_space;
    std::vector<const snmp::storage *> _fixed_disks;
};

template <>
bool sys_info::supports<sys_info::physical_memory>() const
{
    return _physical_memory != nullptr;
}

template <>
std::int64_t sys_info::get<sys_info::physical_memory>() const
{
    return _physical_memory ? _physical_memory->used_space() * _physical_memory->allocation_unit()
                            : 0;
}

template <>
bool sys_info::supports<sys_info::virtual_memory>() const
{
    return _virtual_memory != nullptr;
}

template <>
std::int64_t sys_info::get<sys_info::virtual_memory>() const
{
    return _virtual_memory ? _virtual_memory->used_space() * _virtual_memory->allocation_unit() : 0;
}

template <>
bool sys_info::supports<sys_info::cached_memory>() const
{
    return _cached_memory != nullptr;
}

template <>
std::int64_t sys_info::get<sys_info::cached_memory>() const
{
    return _cached_memory ? _cached_memory->used_space() * _cached_memory->allocation_unit() : 0;
}

template <>
bool sys_info::supports<sys_info::swap_space>() const
{
    return _swap_space != nullptr;
}

template <>
std::int64_t sys_info::get<sys_info::swap_space>() const
{
    return _swap_space ? _swap_space->used_space() * _swap_space->allocation_unit() : 0;
}

template <>
bool sys_info::supports<sys_info::fixed_disks>() const
{
    return _fixed_disks.size() > 0;
}

template <>
std::int64_t sys_info::get<sys_info::fixed_disks>() const
{
    std::int64_t total = 0;
    for (const snmp::storage * disk : _fixed_disks)
    {
        total += disk->used_space() * disk->allocation_unit();
    }
    return total;
}
}
