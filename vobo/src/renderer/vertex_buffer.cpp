#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(float* vertices, int size) {
    /* Generate a buffer to store the vertices in */
    glGenBuffers(1, &renderID_);
    /* bind the current array buffer */
    bind();
    /* place the vertices into the generated buffer */
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &renderID_); }

void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, renderID_); }
void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }