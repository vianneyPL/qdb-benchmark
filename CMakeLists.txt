cmake_minimum_required(VERSION 3.2)
project(qdb-benchmark)
enable_testing()
include(qdb_api.cmake)

set(CMAKE_CXX_STANDARD 11)

if(NOT MSVC)
    add_compile_options(-Wall -pedantic)
endif()

include_directories(${CMAKE_SOURCE_DIR} ${QDB_API_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/thirdparty)
add_subdirectory(bench/app)
add_subdirectory(bench/core)
add_subdirectory(bench/framework)
add_subdirectory(bench/log)
add_subdirectory(bench/tests)
add_subdirectory(utils)

add_executable(qdb-benchmark
    main.cpp
)

target_compile_definitions(qdb-benchmark
	PRIVATE
	-D_CRT_SECURE_NO_WARNINGS # disable VS warning on getenv()
)

target_link_libraries(qdb-benchmark
    bench-app
    bench-core
    bench-log
    bench-tests
)

add_test(help qdb-benchmark --help)
add_test(run qdb-benchmark --threads 1,2,4 --sizes 1,1K,1M)

if(WIN32)
    add_custom_command(TARGET qdb-benchmark POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${QDB_API_DLL}
        $<TARGET_FILE_DIR:qdb-benchmark>)
endif()
