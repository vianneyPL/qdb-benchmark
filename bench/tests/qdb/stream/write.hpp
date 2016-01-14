#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

namespace bench
{
namespace tests
{
namespace qdb
{
namespace stream
{
class write : public qdb_test_template<write>
{
public:
    explicit write(bench::test_config config) : qdb_test_template(config)
    {
    }

    void setup() override
    {
        qdb_test_template::setup();
        _stream = _qdb.stream_open(alias(0), qdb_stream_mode_append);
    }

    void run_iteration(unsigned long iteration)
    {
        _stream.write(content(iteration));
    }

    void cleanup() override
    {
        _stream.close();
        _qdb.remove(alias(0));
        qdb_test_template::cleanup();
    }

    static std::string name()
    {
        return "qdb_stream_write";
    }

    static std::string description()
    {
        return "Each thread repeats qdb_stream_write() on one entry";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    qdb_stream_facade _stream;
};
} // namespace stream
} // namespace qdb
} // namespace tests
} // namespace bench
