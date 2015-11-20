set(FILES
    command_line.hpp
    detailed_error.hpp
    memory.hpp
    random.cpp
    random.hpp
    teamcity.cpp
    teamcity.hpp
    unique_alias.cpp
    unique_alias.hpp
    unique_alias_provider.hpp
)

if (WIN32)
    list(APPEND FILES
        win32.hpp
        win32.cpp
    )
endif()

add_library(utils ${FILES})
target_link_libraries(utils cppformat)
