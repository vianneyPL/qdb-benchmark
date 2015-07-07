add_executable(qdb-benchmark
    main.cpp
)

target_link_libraries(qdb-benchmark
    qdb-benchmark-framework
)

add_test(run-all-test qdb-benchmark)