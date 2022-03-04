#include "element_buffer.h"

ElementBuffer::ElementBuffer(unsigned int* indices, int count) : count_{count} {
    glGenBuffers(1, &renderID_);
    bind();
    /* Link the data to the element/index array buffer indices */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer() { glDeleteBuffers(1, &renderID_); }

void ElementBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID_); }
void ElementBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }