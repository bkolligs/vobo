#ifndef _vertex_array_h_
#define _vertex_array_h_

#include "static_vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace vobo
{
    
/**
 * Vertex Array object in OpenGL
 */
class VertexArray {
   private:
   	bool verbose_;
    bool good_;
   public:
    unsigned int renderID_;
    VertexArray(bool verbose=false);
    ~VertexArray();
    void linkVBO(StaticVertexBuffer& vbo, VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;
    bool good() const {return good_; }
};

} // namespace vobo
#endif  //_vertex_array_h_ header