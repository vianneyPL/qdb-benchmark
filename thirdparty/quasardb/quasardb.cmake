message(STATUS "Looking for quasardb API in ${CMAKE_CURRENT_LIST_DIR}")

find_library(QDB_API
	qdb_api
	HINTS ${CMAKE_CURRENT_LIST_DIR}/lib
)


find_path(QDB_API_INCLUDE_DIR 
	qdb/client.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include
)

if(WIN32)
	find_file(QDB_API_DLL
		qdb_api.dll
		HINTS ${CMAKE_CURRENT_LIST_DIR}/bin
	)
endif()
