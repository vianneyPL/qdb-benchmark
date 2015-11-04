#pragma once

#include <bench/tests/mongodb/mongodb_facade.hpp>
#include <bench/tests/test_template.hpp>
#include <utils/random.hpp>
#include <utils/unique_alias.hpp>

namespace bench
{
namespace tests
{
namespace mongodb
{

template <typename Derived>
class mongodb_test_template : public test_template<Derived>
{
public:
    mongodb_test_template(test_config config) : test_template<Derived>(config)
    {
    }

    void setup() override
    {
    }

protected:
    mongodb_facade _mongodb;

    const std::string & alias(unsigned long iteration) const
    {
        _alias.set_watermark(iteration);
        return _alias;
    }

private:
    mutable utils::unique_alias _alias;
};

} // namespace mongodb
} // namespace tests
} // namespace bench
