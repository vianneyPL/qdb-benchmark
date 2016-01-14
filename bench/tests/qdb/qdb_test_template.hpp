#pragma once

#include <bench/tests/common/test_template.hpp>
#include <bench/tests/qdb/node_status.hpp>
#include <bench/tests/qdb/quasardb_facade.hpp>
#include <utils/unique_alias_provider.hpp>
#include <utils/unique_content_provider.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
template <typename Derived>
class qdb_test_template : public test_template<Derived>,
                          protected utils::unique_alias_provider,
                          protected utils::unique_content_provider
{
public:
    qdb_test_template(test_config config)
        : test_template<Derived>(config), unique_content_provider(config.content_size), _cluster_uri(config.cluster_uri)
    {
    }

    void setup() override
    {
        _qdb.connect(_cluster_uri);
    }

    void cleanup() override
    {
        // _qdb.trim_all(); <- times out
        _qdb.close();
    }

    static probe_collection create_probes(test_config cfg)
    {
        probe_collection probes;
        probes.emplace_back(new node_status(cfg.cluster_uri));
        return probes;
    }

protected:
    quasardb_facade _qdb;

private:
    std::string _cluster_uri;
};

} // namespace qdb
} // namespace tests
} // namespace bench
