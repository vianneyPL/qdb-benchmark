#pragma once

#include <bench/tests/test_template.hpp>
#include <bench/tests/qdb/alias.hpp>
#include <bench/tests/qdb/node_status.hpp>
#include <utils/qdb_wrapper.hpp>
#include <utils/random.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
void set_watermark(std::string & str, unsigned long iteration)
{
    // print decimal representation in reverse order
    for (int digit = 0; digit < 10; digit++)
    {
        if (digit >= str.size()) break;
        str[digit] = iteration % 10;
        iteration /= 10;
    }
}

template <typename Derived>
class qdb_test_template : public test_template<Derived>
{
public:
    qdb_test_template(test_config config) : test_template<Derived>(config)
    {
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
    alias _alias;
};
}
}
}
