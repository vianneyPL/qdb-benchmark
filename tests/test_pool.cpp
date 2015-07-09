#pragma once

#include "test_pool.hpp"
#include "blob_get.hpp"

using namespace qdb::benchmark::tests;

test_pool::test_pool()
{
    _tests.push_back(blob_get::get_class());
}

test_pool::iterator test_pool::begin() const
{
    return _tests.begin();
}

test_pool::iterator test_pool::end() const
{
    return _tests.end();
}