cmake_minimum_required(VERSION 3.16)
project(GLAD LANGUAGES CXX)

set(SOURCES_GLAD
	"glad.h"
	"khrplatform.h"
	"glad.cpp"
)

add_library(glad STATIC ${SOURCES_GLAD})
target_link_libraries(glad ${CMAKE_DL_LIBS})