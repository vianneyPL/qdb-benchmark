#pragma once

#include <bench/tests/cassandra/cassandra_facade.hpp>
#include <bench/tests/test_template.hpp>
#include <utils/random.hpp>
#include <utils/unique_alias_provider.hpp>

namespace bench
{
namespace tests
{
namespace cassandra
{

template <typename Derived>
class cassandra_test_template : public test_template<Derived>, protected utils::unique_alias_provider
{
public:
    cassandra_test_template(test_config config)
        : test_template<Derived>(config), _cluster_uri(config.cluster_uri)
    {
    }

    void setup() override
    {
        _cassandra.connect(_cluster_uri);
    }

    static probe_collection create_probes(test_config cfg)
    {
        probe_collection probes;
        return probes;
    }

protected:
    cassandra_facade _cassandra;

private:
    std::string _cluster_uri;
};

} // namespace cassandra
} // namespace tests
} // namespace bench
