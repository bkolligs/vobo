cmake_minimum_required(VERSION 3.16)
project(VOBO)

add_subdirectory(vobo)
add_subdirectory(sandbox)

# Print out the variables in the current CMAKE context for debuggin the build system
set(PRINT_VARIABLES FALSE CACHE BOOL "Print out the varialbes in the current CMake context")
if (${PRINT_VARIABLES})
	# Prints out all the availiable CMAKE Variables for debugging
	get_cmake_property(_variableNames VARIABLES)
	list (SORT _variableNames)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
endif()