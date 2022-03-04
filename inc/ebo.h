#ifndef _element_buffer_h_
#define _element_buffer_h_

#include "GL/glew.h"

/**
 * Element buffer object for using indices
 */
class EBO {
   public:
    unsigned int id;
    /**
     * Generates an element buffer arrray and links it to indices
     */
    EBO(unsigned int* indices, int size);
    ~EBO();
    void bind();
    void unbind();
};


#endif  //_element_buffer_h_ header