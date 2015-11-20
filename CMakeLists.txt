cmake_minimum_required(VERSION 3.2)
project(qdb-benchmark)
enable_testing()

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)
include(thirdparty/cppformat/cppformat.cmake)
include(thirdparty/mongodb/mongodb.cmake)
include(thirdparty/netsnmp/netsnmp.cmake)
include(thirdparty/quasardb/quasardb.cmake)
add_subdirectory(thirdparty/ArduinoJson/src)

if(NOT MSVC)
    add_compile_options(-Wall -pedantic)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    # Force static build
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(bench/app)
add_subdirectory(bench/core)
add_subdirectory(bench/framework)
add_subdirectory(bench/log)
add_subdirectory(bench/report)
add_subdirectory(bench/tests)
add_subdirectory(utils)

if (${NETSNMP_FOUND})
    add_subdirectory(snmp)
endif()

add_executable(qdb-benchmark
    main.cpp
)

target_compile_definitions(qdb-benchmark
	PRIVATE
	-D_CRT_SECURE_NO_WARNINGS # disable VS warning on getenv()
)

target_link_libraries(qdb-benchmark
    bench-app
    bench-core
    bench-log
    bench-tests
)

add_test(help qdb-benchmark --help)
add_test(help qdb-benchmark --tests qdb_blob_put --sizes 1M)

if(EXISTS ${QDB_API_DLL})
    add_custom_command(TARGET qdb-benchmark POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${QDB_API_DLL}
        $<TARGET_FILE_DIR:qdb-benchmark>)
endif()

set(CPACK_PACKAGE_VERSION "2.0.0")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0) 
include(CPack)
install(TARGETS qdb-benchmark
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if(EXISTS ${QDB_API_DLL})
    install(FILES ${QDB_API_DLL} DESTINATION bin)
endif()

if(EXISTS ${NETSNMP_DLL})
    install(FILES ${NETSNMP_DLL} DESTINATION bin)
endif()

if(EXISTS ${QDB_API})
    install(FILES ${QDB_API} DESTINATION lib)
endif()
