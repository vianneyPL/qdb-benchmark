add_library(qdb-benchmark-framework
    test.hpp
    test_runner.cpp
)

target_include_directories(qdb-benchmark-framework
    PUBLIC ${CMAKE_SOURCE_DIR}/qdb/include
)