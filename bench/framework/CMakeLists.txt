find_package(Threads)

add_library(bench-framework
    test_iteration_probe.hpp
    test_runner.cpp
    test_runner.hpp
    test_thread.hpp
    thread_synchronizer.hpp
    test_thread.hpp
)

if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(bench-framework
        PUBLIC
        -fnon-call-exceptions
    )
endif()

target_link_libraries(bench-framework
	${CMAKE_THREAD_LIBS_INIT}
)