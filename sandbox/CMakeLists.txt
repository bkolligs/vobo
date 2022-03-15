cmake_minimum_required(VERSION 3.16)
project(VOBO_SANDBOX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(sandbox src/sandbox.cpp)
set(SANDBOX_INCLUDE_DIRS
	${VOBO_SOURCE_DIR}/src
)

target_link_libraries(sandbox vobo)
target_include_directories(sandbox PRIVATE ${SANDBOX_INCLUDE_DIRS})