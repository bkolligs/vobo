#include "vertex_buffer_layout.h"

/* Print out the shader source struct nicely */
std::ostream& operator<<(std::ostream& os, const VertexBufferElement& bufferElement) {
    os << "[VertexBufferElements] \n\tBuffer element name: " << bufferElement.name << "\n\t" << bufferElement.count << " objects of type: " << bufferElement.getTypeName() << "\n\t" "Normalized: " << bufferElement.normalized << std::endl;
    return os;
}

VertexBufferLayout::VertexBufferLayout() {}

VertexBufferLayout::~VertexBufferLayout() {}

template <>
void VertexBufferLayout::push<float>(unsigned int count, std::string name) {
    elements_.push_back({name, GL_FLOAT, count, GL_FALSE});
    stride_ += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count,
                                            std::string name) {
    elements_.push_back({name, GL_UNSIGNED_INT, count, GL_FALSE});
    stride_ += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::push<char>(unsigned int count, std::string name) {
    elements_.push_back({name, GL_UNSIGNED_BYTE, count, GL_TRUE});
    stride_ += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}