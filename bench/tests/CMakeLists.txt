set(FILES
    all_tests.cpp
    all_tests.hpp
    std/atomic.hpp
    std/fread.hpp
    std/fwrite.hpp
    std/mutex.hpp
    test_template.hpp
)

set(FLAGS
    -D_CRT_SECURE_NO_WARNINGS
)

set(INCLUDES)
set(LIBRARIES bench-framework)


if(IS_DIRECTORY ${QDB_API_INCLUDE_DIR})
    list(APPEND FLAGS
        -DBENCHMARK_QUASARDB=1
    )

    list(APPEND FILES
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
        qdb/qdb_wrapper.hpp
        qdb/qdb_wrapper.cpp
        qdb/stream/write.hpp
        qdb/tag/add_blob.hpp
    )

    list(APPEND INCLUDES
        ${QDB_API_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/thirdparty # for rapidjson
    )

    list(APPEND LIBRARIES
        ${QDB_API}
    )
else()
    message(STATUS "quasardb client API not found, tests will not be build")
endif()

if(IS_DIRECTORY ${MONGOCLIENT_INCLUDE_DIR})
    list(APPEND FLAGS
        -DBENCHMARK_MONGODB=1
    )

    list(APPEND FILES
        mongodb/blob/get.hpp
        mongodb/blob/put.hpp
        mongodb/blob/update.hpp
        mongodb/integer/add.hpp
        mongodb/mongodb_test_template.hpp
        mongodb/mongodb_wrapper.hpp
    )

    list(APPEND INCLUDES
        ${MONGOCLIENT_INCLUDE_DIR}
    )

    list(APPEND LIBRARIES
        ${MONGOCLIENT}
        ${BOOST_SYSTEM}
        ${BOOST_THREAD}
        ${BOOST_REGEX}
    )
else()
    message(STATUS "mongodb client API not found, tests will not be build")
endif()

add_library(bench-tests ${FILES})
target_compile_options(bench-tests PRIVATE ${FLAGS})
target_include_directories(bench-tests PRIVATE ${INCLUDES})
target_link_libraries(bench-tests ${LIBRARIES})