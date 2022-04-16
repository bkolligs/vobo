#include "static_index_buffer.h"

namespace vobo
{
    
StaticIndexBuffer::StaticIndexBuffer(void* indices, int count) : count_{count} {
    glGenBuffers(1, &renderID_);
    bind();
    /* Link the data to the element/index array buffer indices */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

StaticIndexBuffer::~StaticIndexBuffer() { glDeleteBuffers(1, &renderID_); }

void StaticIndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID_); }
void StaticIndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
} // namespace vobo