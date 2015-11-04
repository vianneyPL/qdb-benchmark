#pragma once

#include <bench/tests/mongodb/mongodb_test_template.hpp>
#include <utils/random.hpp>

namespace bench
{
namespace tests
{
namespace mongodb
{
namespace blob
{
class get : public mongodb_test_template<get>
{
public:
    explicit get(bench::test_config config) : mongodb_test_template(config)
    {
        _content = utils::create_random_string(config.content_size);
    }

    void setup() override
    {
        mongodb_test_template::setup();
        _mongodb.blob_put(alias(0), _content);
    }

    void run_iteration(unsigned long iteration)
    {
        std::string content = _mongodb.blob_get(alias(0));
        if (content != _content) throw std::exception();
    }

    void cleanup() override
    {
        _mongodb.remove(alias(0));
    }

    static std::string name()
    {
        return "mongodb_blob_get";
    }

    static std::string description()
    {
        return "Each thread repeats mongodb.query on a single entry";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _content;
};
} // namespace blob
} // namespace qdb
} // namespace tests
} // namespace bench
