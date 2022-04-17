cmake_minimum_required(VERSION 3.16)
project(VOBO CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(USE_SANITIZER FALSE)
if (${USE_SANITIZER})
	message("Using memory leak sanitizer during compilation!")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -static-libasan -g -fno-omit-frame-pointer")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

set(VOBO_INCLUDE_DIRS
	src
	deps/glm
	deps/glad
	deps/glfw
)

# handle dependencies
add_subdirectory(deps/stb)
add_subdirectory(deps/glm)
add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)


add_library(vobo STATIC)
# collect all the source files from the various subfolders
add_subdirectory(src/cameras)
add_subdirectory(src/core)
add_subdirectory(src/entities)
add_subdirectory(src/renderer)
add_subdirectory(src/window)

target_include_directories(vobo PUBLIC
	${VOBO_INCLUDE_DIRS}
)

target_link_libraries(vobo PUBLIC
	glfw
	sf_libs
	glm::glm
	glad
)

# precompile all the standard library stuff that we use
target_precompile_headers(vobo PUBLIC src/core/vobo_pch.h)
# Set some preprocessor directives that are useful
target_compile_definitions(vobo PUBLIC VOBO_SOURCE_DIR="${VOBO_SOURCE_DIR}/")


# test the vobo library
add_subdirectory(tests)