#ifndef _static_index_buffer_h_
#define _static_index_buffer_h_

#include "glad.h"
#include "log.h"

namespace vobo {

/**
 * Element buffer object for using indices
 */
class StaticIndexBuffer {
    public:
        unsigned int renderID_;
        int count_;
        bool isAllocated_ = false;
        /**
         * Generates an element buffer arrray and links it to indices
         */
        StaticIndexBuffer() = default;
        StaticIndexBuffer(void* indices, int count);
        static StaticIndexBuffer create(void * indices, int count);
        ~StaticIndexBuffer();
        void setIndices(void* indices, int count);
        void bind() const;
        void unbind() const;
        int getCount() const { return count_; }
        unsigned int getID() const { return renderID_; }
        bool good() const {return isAllocated_;}
};

}  // namespace vobo
#endif  //_static_index_buffer_h_ header