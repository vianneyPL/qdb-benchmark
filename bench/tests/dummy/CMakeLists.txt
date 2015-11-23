add_library(bench-tests-dummy INTERFACE)

target_sources(bench-tests-dummy 
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/cleanup_fail.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy_tests.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/setup_fail.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_fail.hpp
)
