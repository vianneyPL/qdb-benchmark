add_library(qdb-bench-app
    command_line.hpp
    program.cpp
    program.hpp
)

target_link_libraries(qdb-bench-app
    qdb-bench-framework
    qdb-bench-tests
)
