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
    HINTS ${CMAKE_CURRENT_LIST_DIR}/lib
)

if(NOT EXISTS ${NETSNMP_LIBRARY})
    message(STATUS "Could NOT find netsnmp library")
    return()
endif()

message(STATUS "Found netsnmp library: ${NETSNMP_LIBRARY}")

find_path(NETSNMP_INCLUDE 
    net-snmp/version.h
    HINTS ${CMAKE_CURRENT_LIST_DIR}/include
)

if(NOT IS_DIRECTORY ${NETSNMP_INCLUDE})
    message(STATUS "Could NOT find netsnmp include directory")
    return()
endif()

add_library(netsnmp SHARED IMPORTED GLOBAL)
set_target_properties(netsnmp 
    PROPERTIES 
    IMPORTED_LOCATION ${NETSNMP_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${NETSNMP_INCLUDE}
)
