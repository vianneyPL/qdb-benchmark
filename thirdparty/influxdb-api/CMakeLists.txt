
project(influxdb-api)

set(CMAKE_CXX_STANDARD 14)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3")

find_package(cppnetlib)
include_directories(${CMAKE_SOURCE_DIR})

set(CPPNETLIB_INCLUDE_DIRS ${CPPNETLIB_INCLUDE_DIRS} ../cpp-netlib/deps/asio/asio/include)
include_directories ( ${CPPNETLIB_INCLUDE_DIRS} )
add_library(${PROJECT_NAME}
    command/create.hpp
    command/drop.hpp
    command/insert.hpp
    command/query.hpp
    command.hpp
    api.cpp
    api.hpp
    measurement/tag.hpp
    measurement/field.hpp
    measurement.cpp
    measurement.hpp
)

target_link_libraries(${PROJECT_NAME}
    cppnetlib-client-connections
    cppnetlib-uri
    cppformat
    pthread
)

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CPPNETLIB_INCLUDE_DIRS} thirdparty/cpp-netlib/deps/asio/asio/include)

set(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
install(FILES ${PROJECT_NAME} DESTINATION lib)