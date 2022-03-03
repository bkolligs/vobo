#include "vao.h"

VAO::VAO() { glGenVertexArrays(1, &id); }

VAO::~VAO() { free(); }

void VAO::linkVBO(VBO& vbo, unsigned int layout) {
    vbo.bind();
    /* Define the attributes of this buffer object */
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, 0);
    /* Tell OpenGL what the layout of the linked buffer object is  */
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO::bind() { glBindVertexArray(id); }
void VAO::unbind() { glBindVertexArray(0); }
void VAO::free() { glDeleteVertexArrays(1, &id); }