add_library(bench-app
    program.cpp
    program.hpp
    settings.hpp
    command_line.cpp
    command_line.hpp
)

target_link_libraries(bench-app
    bench-framework
    bench-report
)