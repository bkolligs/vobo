#ifndef _element_buffer_h_
#define _element_buffer_h_

#include "GL/glew.h"

/**
 * Element buffer object for using indices
 */
class ElementBuffer {
   public:
    unsigned int renderID_;
    int count_;
    /**
     * Generates an element buffer arrray and links it to indices
     */
    ElementBuffer(unsigned int* indices, int count);
    ~ElementBuffer();
    void bind() const;
    void unbind() const;
    int getCount() const { return count_; }
};

#endif  //_element_buffer_h_ header