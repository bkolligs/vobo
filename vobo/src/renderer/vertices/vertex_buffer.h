#ifndef _vertex_buffer_h_
#define _vertex_buffer_h_

#include "glad.h"

/**
 * Vertex buffer object for OpenGL
 */

namespace vobo
{
    

class VertexBuffer {
   public:
    unsigned int renderID_;
    VertexBuffer(const void* vertices, size_t size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};

} // namespace vobo
#endif  //_vertex_buffer_h_ header