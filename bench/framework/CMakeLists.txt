find_package(Threads)

add_library(bench-framework
    test_iteration_probe.hpp
    test_runner.cpp
    test_runner.hpp
    test_thread.hpp
)

target_link_libraries(bench-framework
	${CMAKE_THREAD_LIBS_INIT}
)