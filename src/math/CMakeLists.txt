set(
	HEADERS
	include/math/Operation.hpp
	include/math/Value.hpp
)

set(
	SOURCES
	src/Value.cpp
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
