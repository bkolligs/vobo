#ifndef _renderer_h_
#define _renderer_h_


#include "glad.h"
#include "vobo_memory.h"
#include "log.h"
#include "vobo_pch.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"
#include "primitive_library.h"

namespace vobo
{

class Renderer
{
private:
	unsigned int renderID_; 
	Ref<PrimitiveLibrary> primitiveLibrary_;
	
public:
	Renderer(/* args */);
	~Renderer();
	void beginScene();
	void submit();
	void endScene();
	void clear(const std::array<float, 4> backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f});
	void draw(const VertexArray& va, const IndexBuffer& eb, const Shader& shader) const;
};

} // namespace vobo
#endif //_renderer_h_ header