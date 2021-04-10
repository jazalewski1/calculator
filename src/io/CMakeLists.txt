set(
	HEADERS
	include/io/StringReader.hpp
)

set(
	SOURCES
	src/StringReader.cpp
)

add_library(
	io
	${HEADERS}
	${SOURCES}
)

target_include_directories(
	io
	PUBLIC include
	PRIVATE src
)

target_link_libraries(
	io
	model
	util
)