cmake_minimum_required(VERSION 3.2)
project(qdb-benchmark)
enable_testing()
include(qdb_api.cmake)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(bench/app)
add_subdirectory(bench/framework)
add_subdirectory(bench/tests)

add_executable(qdb-benchmark
    main.cpp
)

target_link_libraries(qdb-benchmark
    qdb-bench-app
)

add_test(run-help qdb-benchmark --help)
add_test(run-with-no-param qdb-benchmark)

if(WIN32)
    add_custom_command(TARGET qdb-benchmark POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${QDB_API_DLL}
        $<TARGET_FILE_DIR:qdb-benchmark>)
endif()
