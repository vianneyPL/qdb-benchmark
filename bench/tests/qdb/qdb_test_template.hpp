#pragma once

#include <bench/tests/test_template.hpp>
#include <bench/tests/qdb/node_status.hpp>
#include <utils/qdb_wrapper.hpp>
#include <utils/random.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
std::string create_unique_prefix();

template <typename Derived>
class qdb_test_template : public test_template<Derived>
{
public:
    qdb_test_template(test_config config) : test_template<Derived>(config)
    {
        _alias_prefix = create_unique_prefix();
        _qdb.connect(config.cluster_uri);
    }

    static probe_collection create_probes(test_config cfg)
    {
        probe_collection probes;
        probes.emplace_back(new node_status(cfg.cluster_uri));
        return probes;
    }

protected:
    utils::qdb_wrapper _qdb;

    std::string get_alias(unsigned long iteration) const
    {
        return _alias_prefix + std::to_string(iteration);
    }

private:
    std::string _alias_prefix;
};
}
}
}
