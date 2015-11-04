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
class update : public mongodb_test_template<update>
{
public:
    explicit update(bench::test_config config) : mongodb_test_template(config)
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
        _mongodb.blob_update(alias(0), _content);
    }

    void cleanup() override
    {
        _mongodb.remove(alias(0));
    }

    static std::string name()
    {
        return "mongodb_blob_update";
    }

    static std::string description()
    {
        return "Each thread repeats mongodb.update on a single entry";
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
