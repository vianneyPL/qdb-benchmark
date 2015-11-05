if(WIN32)
    find_file(QDB_API_DLL
        qdb_api.dll
        HINTS ${CMAKE_CURRENT_LIST_DIR}/bin
    )
endif()

if(EXISTS ${QDB_API_DLL})
    message(STATUS "Found qdb_api.dll: ${QDB_API_DLL}")
endif()

find_library(QDB_API
	qdb_api
	HINTS ${CMAKE_CURRENT_LIST_DIR}/lib
)

if(EXISTS ${QDB_API})
    message(STATUS "Found qdb_api library: ${QDB_API}")
else()
    message(STATUS "Could NOT find qdb_api library")
    return()
endif()

find_path(QDB_API_INCLUDE_DIR 
    qdb/client.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include
)

if(IS_DIRECTORY ${QDB_API_INCLUDE_DIR})
    message(STATUS "Found qdb_api include directory: ${QDB_API_INCLUDE_DIR}")
else()
    message(STATUS "Could NOT find qdb_api include directory")
    return()
endif()
