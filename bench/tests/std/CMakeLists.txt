add_library(bench-tests-std INTERFACE)

target_sources(bench-tests-std 
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/atomic.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fread.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fwrite.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mutex.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/file_exception.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/std_tests.hpp
)
