if(NOT Boost_FOUND)
    message(STATUS "Boost libraries not found, disabling mongodb")
    return()
endif()

find_library(MONGOCLIENT_LIBRARY
	mongoclient
	HINTS ${CMAKE_CURRENT_LIST_DIR}/lib
)

if(NOT EXISTS ${MONGOCLIENT_LIBRARY})
    message(STATUS "Could NOT find mongoclient library")
    return()
endif()

message(STATUS "Found mongoclient library: ${MONGOCLIENT_LIBRARY}")

find_path(MONGOCLIENT_INCLUDE 
    mongo/config.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include
)

if(NOT IS_DIRECTORY ${MONGOCLIENT_INCLUDE})
    message(STATUS "Could NOT find mongoclient include directory")
    return()
endif()

add_library(mongoclient STATIC IMPORTED GLOBAL)
set_target_properties(mongoclient 
    PROPERTIES 
    IMPORTED_LOCATION ${MONGOCLIENT_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${MONGOCLIENT_INCLUDE}
    INTERFACE_LINK_LIBRARIES "${Boost_SYSTEM_LIBRARY};${Boost_THREAD_LIBRARY};${Boost_REGEX_LIBRARY}"
)
