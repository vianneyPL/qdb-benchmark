#pragma once

#include <bench/core/test_class.hpp>
#include <bench/core/test_instance.hpp>

#include <string>
#include <vector>
#include <memory>

namespace qdb {
namespace bench {
namespace framework {

class test_scheduler
{   
public:
    test_scheduler(const     test_scheduler&) =delete;

    test_scheduler() {}

    void set_cluster(std::string cluster)
    {
        _cluster = cluster;
    }

    void set_threads(std::vector<int> threads)
    {
        _threads = threads;
    }

    void add_test_class(const test_class& test_class)
    {
        _test_classes.push_back(&test_class);
        test_config config;
    }

    template<typename Function>
    void for_each(Function fn) const
    {
        test_config config;
        config.cluster_uri = _cluster;

        for (const test_class* tst : _test_classes)
        {
            for (int thr : _threads)
            {
                config.thread_count = thr;
                auto test = tst->instanciate(config);
                fn(*test);
            }
        }
    }


private:
    std::string _cluster;
    std::vector<int> _threads;
    std::vector<const test_class*> _test_classes;
};

}}}