set(
	HEADERS
	include/util/Exception.hpp
)

add_library(
	util
	${HEADERS}
)

target_include_directories(
	util
	PUBLIC include
	PRIVATE src
)

set_target_properties(
	util
	PROPERTIES
	LINKER_LANGUAGE CXX
)