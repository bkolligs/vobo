#include <GL/glew.h>
#include "log.h"
#include "vobo_pch.h"
#include "vertex_array.h"
#include "element_buffer.h"
#include "shader.h"

class Renderer
{
private:
	unsigned int renderID_; 
public:
	Renderer(/* args */);
	~Renderer();
	void clear(const std::array<float, 4> backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f});
	void draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader) const;
};

