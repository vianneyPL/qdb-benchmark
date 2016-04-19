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
class update : public mongodb_test_template<update>
{
public:
    explicit update(bench::test_config config) : mongodb_test_template(config)
    {
    }

    void setup() override
    {
        mongodb_test_template::setup();
        _mongodb.blob_put(alias(0), content(0));
    }

    void run_iteration(std::uint32_t iteration)
    {
        _mongodb.blob_update(alias(0), content(iteration));
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
};
} // namespace blob
} // namespace mongodb
} // namespace tests
} // namespace bench
