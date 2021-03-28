cmake_minimum_required(VERSION 3.18)
project(Calculator)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=switch")
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY "https://github.com/google/googletest.git"
	GIT_TAG master
)
FetchContent_MakeAvailable(googletest)
enable_testing()

set(CMAKE_UTILITIES ${PROJECT_SOURCE_DIR}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(TEST_EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/test)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/math)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/model)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/util)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)