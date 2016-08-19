#pragma once

#include <bench/core/probe.hpp>
#include <bench/tests/mongodb/mongodb_facade.hpp>

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
        // clang-format off
        define_measurement("mongodb.db.storage_size", "MongoDB: Database Storage Size", unit::bytes, 1);
        define_measurement("mongodb.db.objects",      "MongoDB: Database objects",      unit::none, 1);
        // clang-format on
    }

    void take_sample() override
    {
        auto status = mongodb_facade::db_status(_cluster_uri);

        set_measured_value("mongodb.db.storage_size", 0, static_cast<std::int64_t>(status["storageSize"].Double()));
        set_measured_value("mongodb.db.objects", 0, static_cast<std::int64_t>(status["objects"].Int()));
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
