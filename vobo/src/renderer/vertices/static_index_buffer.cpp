#include "static_index_buffer.h"

namespace vobo {

StaticIndexBuffer::StaticIndexBuffer(void* indices, int count) : count_{count} {
    setIndices(indices, count);
}

void StaticIndexBuffer::setIndices(void* indices, int count) {
    if (isAllocated_) {
        VOBO_WARNING_LOG(
            "[StaticIndexBuffer] Overwriting data in current buffer: "
            << renderID_);
        isAllocated_ = false;
    } else {
        glGenBuffers(1, &renderID_);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID_);
    int currentlyBound;
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentlyBound);
    VOBO_INFO_LOG("Currenlty bound! " << currentlyBound);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices,
                 GL_STATIC_DRAW);
    isAllocated_ = true;
}
StaticIndexBuffer::~StaticIndexBuffer() { glDeleteBuffers(1, &renderID_); }

void StaticIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID_);
}
void StaticIndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}  // namespace vobo