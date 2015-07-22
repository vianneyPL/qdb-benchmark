add_library(qdb-bench-tests
	qdb/blob_get.hpp
	qdb/blob_update.hpp
	qdb/queue_push_back.hpp
	qdb/test_base.hpp
    all_tests.cpp
    all_tests.hpp
	test_template.hpp
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