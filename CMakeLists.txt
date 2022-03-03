cmake_minimum_required(VERSION 3.16)
project(OCULOBO CXX)
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

add_library(main_window 
	src/main_window
	src/shader_loader
)
target_link_libraries(main_window
	OpenGL::GL
	glfw
	GLEW
)

add_executable(triangle src/triangle)
target_link_libraries(triangle
	main_window
	OpenGL::GL
	glfw
	GLEW
)

# Testing executable for openGL
add_executable(test src/test)
target_link_libraries(test
	main_window
	OpenGL::GL
	glfw
	GLEW
)