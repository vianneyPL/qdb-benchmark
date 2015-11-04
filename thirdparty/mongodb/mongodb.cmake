message(STATUS "Looking for mongodb API in ${CMAKE_CURRENT_LIST_DIR}")

find_library(MONGOCLIENT
	mongoclient
	HINTS ${CMAKE_CURRENT_LIST_DIR}/lib
)

find_path(MONGOCLIENT_INCLUDE_DIR 
	mongo/config.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include
)

find_library(BOOST_SYSTEM
    boost_system
)

find_library(BOOST_THREAD
    boost_thread
)

find_library(BOOST_REGEX
    boost_regex
)

find_path(BOOST_INCLUDE_DIR 
    boost/version.hpp
)
