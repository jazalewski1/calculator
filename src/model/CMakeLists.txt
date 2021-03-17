set(
	HEADERS
	include/model/Calculator.hpp
	include/model/OperationData.hpp
)

set(
	SOURCES
	src/Calculator.cpp
)

add_library(
	model
	${HEADERS}
	${SOURCES}
)

target_include_directories(
	model
	PUBLIC include
	PRIVATE src
)

target_link_libraries(
	model
	math
)