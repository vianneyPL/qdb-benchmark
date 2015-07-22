add_library(qdb-bench-app
    program.cpp
    program.hpp
    settings.hpp
    command_line.cpp
    command_line.hpp
)

target_link_libraries(qdb-bench-app
    qdb-bench-framework
)