set(
	HEADERS
	include/model/Calculator.hpp
	include/model/PostfixToken.hpp
	include/model/Reader.hpp
)

set(
	SOURCES
	src/Calculator.cpp
	src/InfixToken.cpp
	src/InfixToPostfix.cpp
	src/PostfixToken.cpp
	src/Reader.cpp
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
	util
)