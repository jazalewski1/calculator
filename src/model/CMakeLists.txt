set(
	HEADERS
	include/model/Calculator.hpp
	include/model/PostfixSymbol.hpp
)

set(
	SOURCES
	src/Calculator.cpp
	src/InfixSymbol.cpp
	src/PostfixSymbol.cpp
	src/InfixToPostfix.cpp
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