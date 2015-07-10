add_library(qdb-bench-tests
    blob_get.hpp
    test_pool.cpp
    test_pool.hpp
)

target_link_libraries(qdb-bench-tests
    qdb-bench-framework
)

target_include_directories(qdb-bench-tests
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)