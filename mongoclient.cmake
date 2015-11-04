set(MONGODB_DIR ${CMAKE_SOURCE_DIR}/mongodb)

find_library(MONGOCLIENT
	mongoclient
	HINTS ${MONGODB_DIR}/lib
)

find_path(MONGOCLIENT_INCLUDE_DIR 
	mongo/config.h
        HINTS ${MONGODB_DIR}/include
)
