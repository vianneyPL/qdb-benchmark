add_library(snmp
    oid.cpp
    oid.hpp
    session.cpp
    session.hpp
    storage.cpp
    storage.hpp
    sys_info.hpp
    variant.hpp
)

target_link_libraries(snmp netsnmp)

add_executable(snmp-example
    example.cpp
)

target_link_libraries(snmp-example
    snmp
)

add_test(snmp-example snmp-example)
