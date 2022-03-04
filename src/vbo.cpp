#include "vbo.h"

VBO::VBO(float* vertices, int size) {
    /* Generate a buffer to store the vertices in */
    glGenBuffers(1, &id);
    /* bind the current array buffer */
    bind();
    /* place the vertices into the generated buffer */
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO() { glDeleteBuffers(1, &id); }

void VBO::bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }
void VBO::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }