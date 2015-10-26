add_library(bench-tests
    qdb/blob/add_tag.hpp
    qdb/blob/get.hpp
    qdb/blob/get_noalloc.hpp
    qdb/blob/put.hpp
    qdb/blob/remove.hpp
    qdb/blob/update.hpp
    qdb/deque/pop_back.hpp
    qdb/deque/pop_front.hpp
    qdb/deque/push_back.hpp
    qdb/deque/push_front.hpp
    qdb/hset/contains.hpp
    qdb/hset/erase.hpp
    qdb/hset/insert.hpp
    qdb/integer/add.hpp
    qdb/integer/get.hpp
    qdb/integer/put.hpp
    qdb/integer/remove.hpp
    qdb/integer/update.hpp
    qdb/node_status.hpp
    qdb/qdb_test_template.hpp
    qdb/stream/write.hpp
    qdb/tag/add_blob.hpp
    std/atomic.hpp
    std/fread.hpp
    std/fwrite.hpp
    std/mutex.hpp

    all_tests.cpp
    all_tests.hpp
    test_template.hpp
)

target_compile_options(bench-tests
    PRIVATE
    -D_CRT_SECURE_NO_WARNINGS
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