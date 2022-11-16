target_sources(vobo PUBLIC
	shader.cpp
	texture.cpp
	renderer.cpp
)

add_subdirectory(vertices)

target_include_directories(vobo PUBLIC .)