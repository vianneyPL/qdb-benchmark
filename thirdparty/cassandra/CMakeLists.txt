find_library(CASSANDRA_LIBRARY
	cassandra
	HINTS ${CMAKE_CURRENT_LIST_DIR}/lib
)

if(NOT EXISTS ${CASSANDRA_LIBRARY})
    message(STATUS "Could NOT find cassandra library")
    return()
endif()

message(STATUS "Found cassandra library: ${CASSANDRA_LIBRARY}")

find_path(CASSANDRA_INCLUDE 
    cassandra.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include
)

if(NOT IS_DIRECTORY ${CASSANDRA_INCLUDE})
    message(STATUS "Could NOT find cassandra include directory")
    return()
endif()

add_library(cassandra SHARED IMPORTED GLOBAL)
set_target_properties(cassandra 
    PROPERTIES 
    IMPORTED_LOCATION ${CASSANDRA_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${CASSANDRA_INCLUDE}
)