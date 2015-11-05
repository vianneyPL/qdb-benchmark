set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS regex system thread)

if(NOT Boost_FOUND)
    message(STATUS "Boost libraries not found, disabling mongodb")
    return()
endif()

find_library(MONGOCLIENT
	mongoclient
	HINTS ${CMAKE_CURRENT_LIST_DIR}/lib
)

if(EXISTS ${MONGOCLIENT})
    message(STATUS "Found mongoclient library: ${MONGOCLIENT}")
else()
    message(STATUS "Could NOT find mongoclient library")
endif()

find_path(MONGOCLIENT_INCLUDE_DIR 
    mongo/config.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include
)

if(IS_DIRECTORY ${MONGOCLIENT_INCLUDE_DIR})
    message(STATUS "Found mongoclient include directory: ${MONGOCLIENT_INCLUDE_DIR}")
else()
    message(STATUS "Could NOT find mongoclient include directory")
endif()
