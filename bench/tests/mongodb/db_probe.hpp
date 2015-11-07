#pragma once

#include <bench/core/probe.hpp>
#include <bench/tests/mongodb/mongodb_facade.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace bench
{
namespace tests
{
namespace mongodb
{

class db_probe : public probe
{
public:
    db_probe(std::string cluster_uri) : _cluster_uri(cluster_uri)
    {
    }

    void setup() override
    {
    }

    void take_sample(time_point now, result_type & result) override
    {
        std::vector<std::int64_t> storage_size, objects;

        auto db_status = mongodb_facade::db_status(_cluster_uri);

        storage_size.push_back(static_cast<std::int64_t>(db_status["storageSize"].Int()));
        objects.push_back(db_status["objects"].Int());

        result["db_storage_size"].push_back({now, storage_size});
        result["db_objects"].push_back({now, objects});
    }

    void cleanup() override
    {
    }

private:
    std::string _cluster_uri;
};

} // namespace mongodb
} // namespace tests
} // namespace bench
