#include "static_vertex_buffer.h"

namespace vobo {

StaticVertexBuffer::StaticVertexBuffer(const void* vertices, size_t size) {
    /* Generate a buffer to store the vertices in */
    glGenBuffers(1, &renderID_);
    /* bind the current array buffer */
    bind();
    /* place the vertices into the generated buffer */
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    isAllocated_ = true;
}

StaticVertexBuffer::~StaticVertexBuffer() { glDeleteBuffers(1, &renderID_); }

void StaticVertexBuffer::setVertices(const void* vertices, size_t size) {
    if (isAllocated_) {
        VOBO_WARNING_LOG(
            "[StaticVertexBuffer] Overwriting data in current buffer: "
            << renderID_);
        isAllocated_ = false;
    } else {
        glGenBuffers(1, &renderID_);
    }
    /* Bind this buffer */
    bind();
    /* Place the vertices into the buffer */
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    isAllocated_ = true;
}

void StaticVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, renderID_);
}
void StaticVertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

}  // namespace vobo