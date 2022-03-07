cmake_minimum_required(VERSION 3.16)
project(VOBO CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


set(USE_SANITIZER FALSE)
if (${USE_SANITIZER})
	message("Using memory leak sanitizer during compilation!")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -static-libasan -g -fno-omit-frame-pointer")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(inc)

add_library(vobo 
	src/main_window.cpp
	src/shader.cpp
	src/vertex_buffer.cpp
	src/vertex_buffer_layout.cpp
	src/vertex_array.cpp
	src/element_buffer.cpp
	src/error_display.cpp
	src/renderer.cpp
)

# precompile all the standard library stuff that we use
target_precompile_headers(vobo PUBLIC inc/vobo_pch.h)

target_link_libraries(vobo
	OpenGL::GL
	glfw
	GLEW
)