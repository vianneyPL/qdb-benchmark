cmake_minimum_required(VERSION 3.2)
project(qdb-benchmark)
enable_testing()

set(QDB_API_IMPORT_LIBRARY ${CMAKE_SOURCE_DIR}/qdb/lib/${CMAKE_IMPORT_LIBRARY_PREFIX}qdb_api${CMAKE_IMPORT_LIBRARY_SUFFIX})
set(QDB_API_SHARED_LIBRARY ${CMAKE_SOURCE_DIR}/qdb/bin/${CMAKE_SHARED_LIBRARY_PREFIX}qdb_api${CMAKE_SHARED_LIBRARY_SUFFIX})
set(QDBD_EXECUTABLE        ${CMAKE_SOURCE_DIR}/qdb/bin/qdbd${CMAKE_EXECUTABLE_SUFFIX})

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
        ${QDB_API_SHARED_LIBRARY}
        $<TARGET_FILE_DIR:qdb-benchmark>)
endif()

add_custom_command(TARGET qdb-benchmark POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/bench/report/html_template
    $<TARGET_FILE_DIR:qdb-benchmark>/html_template)