#pragma once

#include <bench/tests/test_template.hpp>
#include <bench/tests/qdb/node_status.hpp>
#include <utils/qdb_wrapper.hpp>
#include <utils/random.hpp>

#include <qdb/client.h>

#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>

namespace bench
{
namespace tests
{
namespace qdb
{
template <typename Derived>
class test_base : public test_template<Derived>
{
public:
    test_base(test_config config) : _config(config)
    {
        _alias = create_unique_alias();
    }

    static probe_collection create_probes(test_config cfg)
    {
        probe_collection probes;
        probes.emplace_back(new node_status(cfg.cluster_uri));
        return probes;
    }

    void setup() override
    {
        _qdb.connect(_config.cluster_uri);
    }

    void cleanup() override
    {
    }

protected:
    std::string _alias;
    utils::qdb_wrapper _qdb;
    test_config _config;

private:
    static std::string create_unique_alias()
    {
        static int alias_counter;
        std::ostringstream s;

        s << "benchmarks-";
        s << std::chrono::duration_cast<std::chrono::seconds>(
                 std::chrono::steady_clock::now().time_since_epoch()).count();
        s << "-" << alias_counter;

        alias_counter++;

        return s.str();
    }
};
}
}
}
