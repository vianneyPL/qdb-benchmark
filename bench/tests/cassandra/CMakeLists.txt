if(NOT TARGET cassandra)
    message(STATUS "Not building cassandra tests")
    return()
endif()

add_library(bench-tests-cassandra
    blob/get.hpp
    blob/put.hpp
    blob/update.hpp
    cassandra_test_template.hpp
    cassandra_facade.cpp
    cassandra_facade.hpp
    cassandra_tests.hpp
    server_probe.hpp
)
target_compile_options(bench-tests-cassandra
    INTERFACE
    -DBENCHMARK_CASSANDRA=1
)
target_link_libraries(bench-tests-cassandra 
    cassandra
)
