add_library(qdb-benchmark-framework
    chronometer.hpp
    test_runner.cpp
    test_runner.hpp
    test_scheduler.hpp
)

target_include_directories(qdb-benchmark-framework
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/qdb/include
)

target_link_libraries(qdb-benchmark-framework
    ${QDB_API_IMPORT_LIBRARY}
)
