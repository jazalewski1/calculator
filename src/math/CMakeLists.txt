set(
	HEADERS
	include/math/Operation.hpp
	include/math/ValuePtr.hpp
)

set(
	SOURCES
	src/Operation.cpp
)

add_library(
	math
	${HEADERS}
	${SOURCES}
)

target_include_directories(
	math
	PUBLIC include
	PRIVATE src
)
