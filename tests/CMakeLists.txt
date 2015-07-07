add_library(qdb-benchmark-tests
    blob_get.hpp
    test_pool.cpp
    test_pool.hpp
)

target_link_libraries(qdb-benchmark-tests
    qdb-benchmark-framework
)

target_include_directories(qdb-benchmark-tests
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)