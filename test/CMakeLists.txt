include(${CMAKE_UTILITIES}/AddTestModule.cmake)

set(EXECUTABLE_OUTPUT_PATH ${TEST_EXECUTABLE_OUTPUT_PATH})

add_test_module(
	NAME OperationTests
	PATH math/OperationTests.cpp
	DEPENDS
	gtest
	gtest_main
	math
)

add_test_module(
	NAME CalculatorTests
	PATH model/CalculatorTests.cpp
	DEPENDS
	gtest
	gtest_main
	model
	util
)