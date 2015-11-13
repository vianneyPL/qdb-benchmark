if(WIN32)
    find_file(NETSNMP_DLL
        netsnmp.dll
        HINTS ${CMAKE_CURRENT_LIST_DIR}/bin
    )

    if(EXISTS ${NETSNMP_DLL})
        message(STATUS "Found netsnmp.dll: ${NETSNMP_DLL}")
    else()
        message(STATUS "Could NOT find netsnmp.dll")
        return()
    endif()
endif()

find_library(NETSNMP_LIBRARY
    netsnmp
    HINTS ${CMAKE_CURRENT_LIST_DIR}/lib C:/usr/lib
)

if(EXISTS ${NETSNMP_LIBRARY})
    message(STATUS "Found netsnmp library: ${NETSNMP_LIBRARY}")
else()
    message(STATUS "Could NOT find netsnmp library")
    return()
endif()

find_path(NETSNMP_INCLUDE_DIR 
    net-snmp/version.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include C:/usr/include
)

if(IS_DIRECTORY ${NETSNMP_INCLUDE_DIR})
    message(STATUS "Found netsnmp include directory: ${NETSNMP_INCLUDE_DIR}")
else()
    message(STATUS "Could NOT find netsnmp include directory")
    return()
endif()

add_compile_options(
    -DBENCHMARK_SNMP=1
)

set(NETSNMP_FOUND TRUE)