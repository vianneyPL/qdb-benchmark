#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>
#include <utils/random.hpp>

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
        _content = utils::create_random_string(config.content_size);
    }

    void setup() override
    {
        qdb_test_template::setup();
        _stream = _qdb.stream_open(alias(0), qdb_stream_mode_write);
    }

    void run_iteration(unsigned long iteration)
    {
        _stream.write(_content);
    }

    void cleanup() override
    {
        _stream.close();
        _qdb.stream_remove(alias(0));
    }

    static ::std::string name()
    {
        return "qdb_stream_write";
    }

    static ::std::string description()
    {
        return "Each thread repeats qdb_stream_write() on one entry";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    ::std::string _content;
    utils::qdb_stream_wrapper _stream;
};
} // namespace stream
} // namespace qdb
} // namespace tests
} // namespace bench
