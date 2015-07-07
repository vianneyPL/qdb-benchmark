cmake_minimum_required(VERSION 3.0)
project(qdb-benchmark)
enable_testing()

set(QDB_API_IMPORT_LIBRARY ${CMAKE_SOURCE_DIR}/qdb/lib/${CMAKE_IMPORT_LIBRARY_PREFIX}qdb_api${CMAKE_IMPORT_LIBRARY_SUFFIX})
set(QDB_API_SHARED_LIBRARY ${CMAKE_SOURCE_DIR}/qdb/bin/${CMAKE_SHARED_LIBRARY_PREFIX}qdb_api${CMAKE_SHARED_LIBRARY_SUFFIX})
set(QDBD_EXECUTABLE        ${CMAKE_SOURCE_DIR}/qdb/bin/qdbd${CMAKE_EXECUTABLE_SUFFIX})

add_subdirectory(app)
add_subdirectory(framework)
add_subdirectory(tests)