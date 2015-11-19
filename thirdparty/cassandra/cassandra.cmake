set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS regex system thread)

if(NOT Boost_FOUND)
    message(STATUS "Boost libraries not found, disabling cassandra")
    return()
endif()

find_library(CASSANDRA
	cassandra
	HINTS ${CMAKE_CURRENT_LIST_DIR}/lib
)

if(EXISTS ${CASSANDRA})
    message(STATUS "Found cassandra library: ${CASSANDRA}")
else()
    message(STATUS "Could NOT find cassandra library")
endif()

find_path(CASSANDRA_INCLUDE_DIR 
    cassandra.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include
)

if(IS_DIRECTORY ${CASSANDRA_INCLUDE_DIR})
    message(STATUS "Found cassandra include directory: ${CASSANDRA_INCLUDE_DIR}")
else()
    message(STATUS "Could NOT find cassandra include directory")
endif()
