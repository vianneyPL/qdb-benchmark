#include <bench/core/test_instance.hpp>
#include <bench/core/probe.hpp>
#include <bench/framework/test_thread.hpp>
#include <bench/log/logger.hpp>

namespace bench
{
namespace framework
{
class test_runner
{
public:
    test_runner(log::logger & logger) : _logger(logger)
    {
    }

#if BENCHMARK_SNMP
    void set_snmp_peers(const std::vector<std::string> & snmp_peers);
#endif

    void run(test_instance & test)
    {
        _test = &test;

        create_threads();
        create_probes();

        if (step1_setup())
        {
            init_test_results();
            step2_test();
        }

        if (!test.config.no_cleanup)
        {
            step3_cleanup();
        }

        destroy_probes();
        destroy_threads();
    }

private:
    void create_threads();
    void destroy_threads();

    void init_test_results();

    bool step1_setup();
    void step2_test();
    void step3_cleanup();

    void create_probes();
    void destroy_probes();

    void setup_probes();
    void sample_probes();
    void cleanup_probes();

    void log_progress()
    {
        _logger.test_progress(*_test);
    }

    log::logger & _logger;

    test_instance * _test;
    thread_synchronizer<test_thread> _synchronizer;
    test_thread_collection _threads;

#if BENCHMARK_SNMP
    std::unique_ptr<probe> _snmp_probe;
#endif
    std::unique_ptr<probe> _counter_probe;
    probe_collection _custom_probes;
    std::vector<probe *> _all_probes;
};
}
}
