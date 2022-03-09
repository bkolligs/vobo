#ifndef _renderer_h_
#define _renderer_h_


#include <GL/glew.h>
#include "log.h"
#include "vobo_pch.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer
{
private:
	unsigned int renderID_; 
public:
	Renderer(/* args */);
	~Renderer();
	void beginScene();
	void submit();
	void endScene();
	void clear(const std::array<float, 4> backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f});
	void draw(const VertexArray& va, const IndexBuffer& eb, const Shader& shader) const;
};

#endif //_renderer_h_ header