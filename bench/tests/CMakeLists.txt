add_library(bench-tests
    qdb/blob_get.hpp
    qdb/blob_get_noalloc.hpp
    qdb/blob_put.hpp
    qdb/blob_remove.hpp
    qdb/blob_update.hpp
    qdb/int_add.hpp
    qdb/int_update.hpp
    qdb/node_status.hpp
    qdb/deque_push_back.hpp
    qdb/test_base.hpp

    all_tests.cpp
    all_tests.hpp
    test_template.hpp
)

target_link_libraries(bench-tests
    bench-framework
)

target_include_directories(bench-tests
    PRIVATE 
    ${QDB_API_INCLUDE_DIR}
)

target_link_libraries(bench-tests
    ${QDB_API}
)