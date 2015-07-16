add_library(qdb-bench-framework
    test_runner.cpp
    test_runner.hpp
)

target_include_directories(qdb-bench-framework
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/qdb/include
)

target_link_libraries(qdb-bench-framework
    ${QDB_API_IMPORT_LIBRARY}
)
