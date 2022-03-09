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

set(VOBO_CAMERAS_SRC
	src/cameras/orthographic_camera.cpp
	src/cameras/perspective_camera.cpp
)

set(VOBO_RENDERER_SRC
	src/renderer/shader.cpp
	src/renderer/index_buffer.cpp
	src/renderer/vertex_buffer.cpp
	src/renderer/vertex_array.cpp
	src/renderer/vertex_buffer_layout.cpp
	src/renderer/texture.cpp
	src/renderer/renderer.cpp
)

set(VOBO_CORE_SRC
	src/core/error_display.cpp
	src/core/vobo_math.cpp
	)
	
set(VOBO_WINDOW_SRC
	src/window/event_handler.cpp
	src/window/window.cpp
)

set(VOBO_INCLUDE_DIRS
	src
	src/core
	src/cameras
	src/vertices
	src/renderer
	src/window
)

# handle dependencies
add_subdirectory(deps/stb)


add_library(vobo STATIC
	${VOBO_CORE_SRC}
	${VOBO_CAMERAS_SRC}
	${VOBO_WINDOW_SRC}
	${VOBO_RENDERER_SRC}
)


# precompile all the standard library stuff that we use
target_precompile_headers(vobo PUBLIC src/core/vobo_pch.h)
# Set some preprocessor directives that are useful
target_compile_definitions(vobo PUBLIC VOBO_SOURCE_DIR="${VOBO_SOURCE_DIR}/")

target_link_libraries(vobo PUBLIC
	OpenGL::GL
	glfw
	GLEW
	sf_libs
)

target_include_directories(vobo PUBLIC
	${VOBO_INCLUDE_DIRS}
)