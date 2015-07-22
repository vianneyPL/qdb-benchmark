set(QDB_DIR ${CMAKE_SOURCE_DIR}/qdb)

find_library(QDB_API
	qdb_api
	HINTS ${QDB_DIR}/lib
)

find_path(QDB_API_INCLUDE_DIR 
	qdb/client.h
    HINTS ${QDB_DIR}/include
)

if(WIN32)
	find_file(QDB_API_DLL
		qdb_api.dll
		HINTS ${QDB_DIR}/bin
	)
endif()
