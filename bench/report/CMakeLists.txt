add_library(bench-report
    jsonp.cpp
    jsonp.hpp
)

target_link_libraries(bench-report
    ArduinoJson
)