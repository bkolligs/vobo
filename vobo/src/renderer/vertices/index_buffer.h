#ifndef _index_buffer_h_
#define _index_buffer_h_

#include "glad.h"

/**
 * Element buffer object for using indices
 */
class IndexBuffer {
   public:
    unsigned int renderID_;
    int count_;
    /**
     * Generates an element buffer arrray and links it to indices
     */
    IndexBuffer(unsigned int* indices, int count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
    int getCount() const { return count_; }
};

#endif  //_index_buffer_h_ header