#ifndef _vertex_buffer_element_h_
#define _vertex_buffer_element_h_

#include <GL/glew.h>
#include "vobo_pch.h"
#include "log.h"

/**
 * Specifies the attributes of a particular block of data inside a vertex buffer
 */
struct VertexBufferElement {
	std::string name;
	unsigned int type;
	unsigned int count;
	bool normalized;

	std::string getTypeName() const {
		switch (type)
		{
			case GL_FLOAT: return "float";
			case GL_UNSIGNED_INT: return "unsigned int";
			case GL_UNSIGNED_BYTE: return "unsigned byte";
		}
		return "Invalid type specified!";
	}

	static unsigned int getSizeOfType( unsigned int type){
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			
		}
		return 0;
	}

	friend std::ostream& operator<<(std::ostream& os, const VertexBufferElement& bufferElement); 
};

/**
 * The layout of a particular vertex buffer's data
 */
class VertexBufferLayout
{
private:
	/* Stride is the number of bytes between vertices */
	unsigned int stride_ = 0;
	std::vector<VertexBufferElement> elements_;
public:

	VertexBufferLayout();
	~VertexBufferLayout();

	template <typename T>
	void push(unsigned int count, std::string name) {}

	const std::vector<VertexBufferElement> & getElements() const {return elements_;}
	unsigned int getStride() {return stride_;}
};

#endif //_vertex_buffer_element_h_ header