add_executable(qdb-benchmark
    main.cpp
)

target_link_libraries(qdb-benchmark
    qdb-benchmark-framework
    qdb-benchmark-tests
)

add_test(run-all-test qdb-benchmark)

if(WIN32)
    add_custom_command(TARGET qdb-benchmark POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${QDB_API_SHARED_LIBRARY}
        $<TARGET_FILE_DIR:qdb-benchmark>)
endif()