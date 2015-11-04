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
class put : public mongodb_test_template<put>
{
public:
    explicit put(bench::test_config config) : mongodb_test_template(config)
    {
        _content = utils::create_random_string(config.content_size);
    }

    void run_iteration(unsigned long iteration)
    {
        _mongodb.blob_put(alias(iteration), _content);
    }

    void cleanup() override
    {
        cleanup_each([=](unsigned long iteration)
                     {
                         _mongodb.remove(alias(iteration));
                     });
    }

    static std::string name()
    {
        return "mongodb_blob_put";
    }

    static std::string description()
    {
        return "Each thread repeats mongodb.insert with new ids";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _content;
};
} // namespace blob
} // namespace mongodb
} // namespace tests
} // namespace bench
