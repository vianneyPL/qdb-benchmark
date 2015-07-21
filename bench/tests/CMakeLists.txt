add_library(qdb-bench-tests
    test_pool.cpp
    test_pool.hpp
)

target_link_libraries(qdb-bench-tests
    qdb-bench-framework
)

target_include_directories(qdb-bench-tests
    PRIVATE 
    ${QDB_API_INCLUDE_DIR}
)

target_link_libraries(qdb-bench-tests
    ${QDB_API}
)