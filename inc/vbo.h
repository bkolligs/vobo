#ifndef _vertex_buffer_h_
#define _vertex_buffer_h_

#include "GL/glew.h"

/**
 * Vertex buffer object for OpenGL
 */
class VBO {
   public:
    unsigned int id;
    VBO(float* vertices, int size);
    ~VBO();
    void bind();
    void unbind();
    void free();
};

#endif  //_vertex_buffer_h_ header