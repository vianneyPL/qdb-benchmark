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

void bench::tests::qdb::set_watermark(std::string & str, unsigned long iteration)
{
    // print decimal representation in reverse order
    for (int digit = 0; digit < 10; digit++)
    {
        if (digit >= str.size()) break;
        str[digit] = iteration % 10;
        iteration /= 10;
    }
}