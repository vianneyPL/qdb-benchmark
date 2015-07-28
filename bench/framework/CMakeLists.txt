find_package(Threads)

add_library(qdb-bench-framework
    probe_sampler.cpp
    probe_sampler.hpp
    test_runner.cpp
    test_runner.hpp
)

target_link_libraries(qdb-bench-framework
	${CMAKE_THREAD_LIBS_INIT}
)