#ifndef _vertex_array_h_
#define _vertex_array_h_

#include "vertex_buffer.h"

/**
 * Vertex Array object in OpenGL
 */
class VertexArray {
   public:
    unsigned int renderID_;
    VertexArray();
    ~VertexArray();
    void linkVBO(VertexBuffer& vbo, unsigned int layout);
    void bind() const;
    void unbind() const;
};

#endif  //_vertex_array_h_ header