#pragma once

#include <bench/core/test_class.hpp>

#include <vector>
#include <memory>

namespace bench {
namespace tests {

class test_pool
{
public:
    class iterator;

    test_pool();
    iterator begin() const;
    iterator end() const;

private:
    typedef std::vector<const bench::test_class*> collection_type;

    collection_type _tests;
};

class test_pool::iterator 
{
    friend class test_pool;

public:
    const bench::test_class& operator*() const { return **_it; }
    iterator operator++() { return ++_it; }
    bool operator!=(const iterator& other) { return other._it != _it; }    

private:
    iterator(test_pool::collection_type::const_iterator& it)
        : _it(it)
    {
    }

    test_pool::collection_type::const_iterator _it;
};

}}