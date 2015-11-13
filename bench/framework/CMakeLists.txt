set(FILES
    counter_probe.hpp
    snmp_probe.hpp
    test_runner.cpp
    test_runner.hpp
    test_thread.hpp
    test_thread.hpp
    thread_synchronizer.hpp
)

set(INCLUDES)

set(LIBRARIES
    utils
    ${CMAKE_THREAD_LIBS_INIT}
)

if(${NETSNMP_FOUND})
    list(APPEND FILES snmp_probe.hpp)
    list(APPEND LIBRARIES snmp)
else()
    message(STATUS "Not building SNMP probe")
endif()

add_library(bench-framework ${FILES})
target_include_directories(bench-framework PRIVATE ${INCLUDES})
target_link_libraries(bench-framework ${LIBRARIES})

if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(bench-framework
        PUBLIC
        -fnon-call-exceptions
    )
endif()
