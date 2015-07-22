add_library(qdb-bench-log
	console_logger.cpp
	console_logger.hpp
	logger.hpp
	teamcity_logger.cpp
	teamcity_logger.hpp
)

target_link_libraries(qdb-bench-log
	qdb-bench-core
)