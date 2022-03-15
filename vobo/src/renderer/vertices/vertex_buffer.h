#ifndef _vertex_buffer_h_
#define _vertex_buffer_h_

#include "glad.h"

/**
 * Vertex buffer object for OpenGL
 */
class VertexBuffer {
   public:
    unsigned int renderID_;
    VertexBuffer(float* vertices, int size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};

#endif  //_vertex_buffer_h_ header