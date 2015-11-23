if(NOT TARGET mongoclient)
    message(STATUS "Not building mongodb tests")
    return()
endif()

add_library(bench-tests-mongodb
    blob/get.hpp
    blob/put.hpp
    blob/update.hpp
    integer/add.hpp

    mongodb_test_template.hpp
    mongodb_facade.cpp
    mongodb_facade.hpp
    mongodb_tests.hpp
)
target_compile_options(bench-tests-mongodb
    INTERFACE -DBENCHMARK_MONGODB=1
)
target_link_libraries(bench-tests-mongodb
    mongoclient
)
