cmake_minimum_required(VERSION 3.0)
project(qdb-benchmark)
enable_testing()

add_executable(qdb-benchmark
    app/main.cpp
)

add_test(run-all-test qdb-benchmark)