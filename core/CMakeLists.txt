add_library(qdb-benchmark-core
    test_result.hpp
    test_config.hpp
    test_instance.hpp
    test_result.hpp
)

target_include_directories(qdb-benchmark-core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)