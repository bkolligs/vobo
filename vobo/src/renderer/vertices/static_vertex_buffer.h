#ifndef _static_vertex_buffer_h_
#define _static_vertex_buffer_h_

#include "glad.h"

/**
 * Vertex buffer object for OpenGL
 */

namespace vobo
{
    

class StaticVertexBuffer {
   public:
    unsigned int renderID_;
    StaticVertexBuffer(const void* vertices, size_t size);
    ~StaticVertexBuffer();
    void bind() const;
    void unbind() const;
};

} // namespace vobo
#endif  //_static_vertex_buffer_h_ header