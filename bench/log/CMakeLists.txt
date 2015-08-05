add_library(bench-log
	console_logger.hpp
    logger.hpp
	logger.cpp
	teamcity_logger.hpp
)

target_link_libraries(bench-log
	bench-core
    utils
)