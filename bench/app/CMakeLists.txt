add_library(qdb-bench-app
    program.cpp
    program.hpp
    settings.hpp
)

target_link_libraries(qdb-bench-app
    qdb-bench-framework
    qdb-bench-tests
)
