#pragma once

#include "test_pool.hpp"
#include "blob_get.hpp"

using namespace qdb::benchmark::tests;

test_pool::test_pool()
{
    _tests.push_back(std::make_unique<blob_get>(1));
    _tests.push_back(std::make_unique<blob_get>(100));
    _tests.push_back(std::make_unique<blob_get>(1<<10));
    _tests.push_back(std::make_unique<blob_get>(10<<10));
    _tests.push_back(std::make_unique<blob_get>(1<<20));
}


test_pool::iterator test_pool::begin() const
{
    return _tests.begin();
}

test_pool::iterator test_pool::end() const
{
    return _tests.end();
}