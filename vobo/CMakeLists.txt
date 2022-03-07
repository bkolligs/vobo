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

set(VOBO_INCLUDE_DIRS
	deps/stb
	inc
)
# handle dependencies
add_subdirectory(deps/stb)


add_library(vobo 
	src/main_window.cpp
	src/shader.cpp
	src/vertex_buffer.cpp
	src/vertex_buffer_layout.cpp
	src/vertex_array.cpp
	src/index_buffer.cpp
	src/error_display.cpp
	src/renderer.cpp
	src/texture.cpp
	src/orthographic_camera.cpp
	src/perspective_camera.cpp
)


# precompile all the standard library stuff that we use
target_precompile_headers(vobo PUBLIC inc/vobo_pch.h)

target_link_libraries(vobo 
	OpenGL::GL
	glfw
	GLEW
	sf_libs
)

# Has to be public since this is a library being pulled into other targets
target_include_directories(vobo PUBLIC
	${VOBO_INCLUDE_DIRS}
)