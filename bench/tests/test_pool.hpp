#pragma once

#include <bench/core/test_class.hpp>

#include <vector>
#include <memory>

namespace bench {
namespace tests {

class test_pool
{
    typedef std::vector<std::unique_ptr<test_class>> collection_type;

public:
    typedef collection_type::const_iterator iterator;

    test_pool();
    iterator begin() const { return _tests.begin(); }
    iterator end() const { return _tests.end(); }

private:
    template<typename TestClass>
    void add();

    collection_type _tests;
};

}}