find_package(Threads)

add_library(qdb-bench-framework
    test_runner.cpp
    test_runner.hpp
)

target_link_libraries(qdb-bench-framework
	${CMAKE_THREAD_LIBS_INIT}
)