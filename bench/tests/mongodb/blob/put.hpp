#pragma once

#include <bench/tests/mongodb/mongodb_test_template.hpp>

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
    }

    void run_iteration(unsigned long iteration)
    {
        _mongodb.blob_put(alias(iteration), content(iteration));
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
};
} // namespace blob
} // namespace mongodb
} // namespace tests
} // namespace bench
