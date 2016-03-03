if(WIN32)
    message(STATUS "Ignoring SNMP in Windows: not supported")
    return()
endif()

include(ExternalProject)
include(CheckFunctionExists)

set(NETSNMP_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/src)
set(NETSNMP_INCLUDE ${CMAKE_BINARY_DIR}/include)
set(NETSNMP_LIBRARY ${CMAKE_BINARY_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}netsnmp${CMAKE_STATIC_LIBRARY_SUFFIX})
set(NETSNMP_LINK_LIBRARIES)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    # clock_gettime is included in 2.17+, before it was in librt
    CHECK_FUNCTION_EXISTS(clock_gettime HAVE_CLOCK_GETTIME)
    if(NOT "${HAVE_CLOCK_GETTIME}")
        list(APPEND NETSNMP_LINK_LIBRARIES rt)
    endif()
endif()

ExternalProject_Add(netsnmp-sources
    URL https://sourceforge.net/projects/net-snmp/files/net-snmp/5.7.3/net-snmp-5.7.3.tar.gz
    URL_MD5 d4a3459e1577d0efa8d96ca70a885e53
    SOURCE_DIR ${NETSNMP_DIRECTORY}
    CONFIGURE_COMMAND ./configure
        --prefix=${CMAKE_BINARY_DIR}
        --disable-agent
        --disable-applications
        --disable-debugging
        --disable-deprecated
        --disable-embedded-perl
        --disable-manuals
        --disable-mib-loading
        --disable-mibs
        --disable-scripts
        --disable-set-support
        --disable-shared
        --enable-minimalist
        --enable-read-only
        --with-default-snmp-version=1
        --with-defaults
        --without-krb5
        --without-openssl
        --without-pkcs
        --without-rpm
    BUILD_COMMAND ${MAKE}
    BUILD_IN_SOURCE 1
    BUILD_BYPRODUCTS ${NETSNMP_LIBRARY}
)

# prevent warning with INTERFACE_INCLUDE_DIRECTORIES
file(MAKE_DIRECTORY ${NETSNMP_INCLUDE})

add_library(netsnmp STATIC IMPORTED GLOBAL)
add_dependencies(netsnmp netsnmp-sources)
set_target_properties(netsnmp
    PROPERTIES
    IMPORTED_LOCATION ${NETSNMP_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${NETSNMP_INCLUDE}
    INTERFACE_LINK_LIBRARIES "${NETSNMP_LINK_LIBRARIES}"
)
