#ifndef _vertex_array_h_
#define _vertex_array_h_

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace vobo
{
    
/**
 * Vertex Array object in OpenGL
 */
class VertexArray {
   private:
   	bool verbose_;
   public:
    unsigned int renderID_;
    VertexArray(bool verbose=false);
    ~VertexArray();
    void linkVBO(VertexBuffer& vbo, VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;
};

} // namespace vobo
#endif  //_vertex_array_h_ header