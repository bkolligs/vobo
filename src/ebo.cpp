#include "ebo.h"

EBO::EBO(unsigned int* indices, int size) {
    glGenBuffers(1, &id);
    bind();
    /* Link the data to the element/index array buffer indices */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::~EBO() { glDeleteBuffers(1, &id); }

void EBO::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
void EBO::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }