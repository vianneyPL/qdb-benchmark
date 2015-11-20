add_library(cppformat
	${CMAKE_CURRENT_LIST_DIR}/format.cc
	${CMAKE_CURRENT_LIST_DIR}/format.h
)

target_include_directories(cppformat
	INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/..
)
