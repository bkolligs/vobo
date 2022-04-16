#ifndef _static_index_buffer_h_
#define _static_index_buffer_h_

#include "glad.h"

namespace vobo
{
    

/**
 * Element buffer object for using indices
 */
class StaticIndexBuffer {
   public:
    unsigned int renderID_;
    int count_;
    /**
     * Generates an element buffer arrray and links it to indices
     */
    StaticIndexBuffer(void* indices, int count);
    ~StaticIndexBuffer();
    void bind() const;
    void unbind() const;
    int getCount() const { return count_; }
};

} // namespace vobo
#endif  //_static_index_buffer_h_ header