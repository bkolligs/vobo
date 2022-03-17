#include "vertex_array.h"

namespace vobo
{
    
VertexArray::VertexArray(bool verbose) : verbose_{verbose} { glGenVertexArrays(1, &renderID_); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &renderID_); }

void VertexArray::linkVBO(VertexBuffer& vbo, VertexBufferLayout& layout) {

	/* Bind the current buffer */
    vbo.bind();
    /* Iterate over the specified elements in our current layout */
    const auto & elements = layout.getElements();
    /* This is the offset of each attribute */
    long int offset = 0; 
    for (int i = 0; i < elements.size(); i++) {
        const auto element = elements[i];

        verbose_ and std::cout << element << "\tOffset: " << offset << "\n\tLocation: "<< i << std::endl;

        /* Enable the vertex attribute array */
        glEnableVertexAttribArray(i);
        /* Specify the layout of the vertex buffer with our elements */
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (void *)offset);
        /* Increment the offset by the size of the last element block */
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const { glBindVertexArray(renderID_); }
void VertexArray::unbind() const { glBindVertexArray(0); }
} // namespace vobo