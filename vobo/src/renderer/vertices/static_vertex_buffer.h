#ifndef _static_vertex_buffer_h_
#define _static_vertex_buffer_h_

#include "glad.h"
#include "log.h"

/**
 * Vertex buffer object for OpenGL
 */

namespace vobo {

class StaticVertexBuffer {
    public:
        unsigned int renderID_;
        /* Is the buffer allocated on the GPU yet? */
        bool isAllocated_    = false;
        StaticVertexBuffer() = default;
        StaticVertexBuffer(const void* vertices, size_t size);
        ~StaticVertexBuffer();
        void setVertices(const void* vertices, size_t size);
        void bind() const;
        void unbind() const;
        unsigned int getID() const { return renderID_; }
        bool good() const { return isAllocated_; }
};

}  // namespace vobo
#endif  //_static_vertex_buffer_h_ header