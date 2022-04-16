#include "static_vertex_buffer.h"

namespace vobo
{
    
StaticVertexBuffer::StaticVertexBuffer(const void* vertices, size_t size) {
    /* Generate a buffer to store the vertices in */
    glGenBuffers(1, &renderID_);
    /* bind the current array buffer */
    bind();
    /* place the vertices into the generated buffer */
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

StaticVertexBuffer::~StaticVertexBuffer() { glDeleteBuffers(1, &renderID_); }

void StaticVertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, renderID_); }
void StaticVertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

} // namespace vobo