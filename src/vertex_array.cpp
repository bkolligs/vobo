#include "vertex_array.h"

VertexArray::VertexArray() { glGenVertexArrays(1, &renderID_); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &renderID_); }

void VertexArray::linkVBO(VertexBuffer& vbo, unsigned int layout) {
    vbo.bind();
    /* Define the attributes of this buffer object */
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, 0);
    /* Tell OpenGL what the layout of the linked buffer object is  */
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VertexArray::bind() const { glBindVertexArray(renderID_); }
void VertexArray::unbind() const { glBindVertexArray(0); }