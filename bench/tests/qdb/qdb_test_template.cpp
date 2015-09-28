#pragma once

#include <bench/tests/qdb/qdb_test_template.hpp>

#include <atomic>
#include <chrono>
#include <sstream>

static std::atomic<int> __counter(0);

std::string bench::tests::qdb::create_unique_prefix()
{
    std::ostringstream s;

    s << "benchmarks-"
      << std::chrono::duration_cast<std::chrono::seconds>(
             std::chrono::steady_clock::now().time_since_epoch())
             .count()
      << "-" << __counter++ << "-";

    return s.str();
}
