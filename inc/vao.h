#ifndef _vertex_array_h_
#define _vertex_array_h_

#include "vbo.h"

/**
 * Vertex Array object in OpenGL
 */
class VAO {
   public:
    unsigned int id;
    VAO();
    ~VAO();
    void linkVBO(VBO& vbo, unsigned int layout);
    void bind();
    void unbind();
};

#endif  //_vertex_array_h_ header