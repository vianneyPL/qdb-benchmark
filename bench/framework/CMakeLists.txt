set(FILES
    counter_probe.hpp
    snmp_probe.hpp
    test_runner.cpp
    test_runner.hpp
    test_thread.hpp
    test_thread.hpp
    thread_synchronizer.hpp
)

set(LIBRARIES
    utils
    ${CMAKE_THREAD_LIBS_INIT}
)

set(DEFINITIONS)

if(TARGET netsnmp)
    list(APPEND FILES snmp_probe.hpp)
    list(APPEND LIBRARIES snmp)
    list(APPEND DEFINITIONS -DBENCHMARK_SNMP=1)
else()
    message(STATUS "Not building SNMP probe")
endif()

add_library(bench-framework ${FILES})
target_link_libraries(bench-framework ${LIBRARIES})
target_compile_definitions(bench-framework PUBLIC ${DEFINITIONS})

if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(bench-framework
        PUBLIC
        -fnon-call-exceptions
    )
endif()
