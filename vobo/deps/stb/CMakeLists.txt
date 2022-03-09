cmake_minimum_required(VERSION 3.16)
project(SF_LIBS LANGUAGES CXX)

set(SOURCES_SF "sf_libs.cpp" "stb_image.h")
add_library(sf_libs STATIC ${SOURCES_SF})
# Add the current directory to any target that links this library
target_include_directories(sf_libs PUBLIC ./)