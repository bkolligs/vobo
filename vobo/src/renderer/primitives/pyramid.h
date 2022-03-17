#ifndef _pyramid_h_
#define _pyramid_h_

#include "glm/glm.hpp"
#include "mesh_object.h"
#include "vobo_pch.h"

namespace vobo {

struct PyramidVertex {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoords;
};

class Pyramid : public MeshObject {
    private:
        /* Add a vector of vertices here that can be used for buffer data */
        std::vector<PyramidVertex> vertices{/* Vertex 0 */
                                            {.position  = {-0.5, 0.0f, 0.5f},
                                             .color     = {0.1f, 0.0f, 0.02f},
                                             .texCoords = {0.0f, 0.0f}},
                                            /* Vertex 1 */
                                            {.position  = {-0.5f, 0.0f, -0.5f},
                                             .color     = {0.8f, 0.3f, 0.02f},
                                             .texCoords = {0.5f, 0.5f}},
                                            /* Vertex 2 */
                                            {.position  = {0.5f, 0.0f, -0.5f},
                                             .color     = {0.2f, 0.8f, 0.12f},
                                             .texCoords = {0.5f, 0.0f}},
                                            /* Vertex 3 */
                                            {.position  = {0.5f, 0.0f, 0.5f},
                                             .color     = {0.8f, 0.3f, 0.02f},
                                             .texCoords = {0.0f, 0.5f}},
                                            /* Vertex 4 */
                                            {.position  = {0.0f, 0.8f, 0.0f},
                                             .color     = {0.1f, 0.1f, 0.92f},
                                             .texCoords = {1.0f, 1.0f}}};

        uint pyramidData[3 * 6] = {0, 1, 2, 0, 2, 3, 0, 1, 4,
                                   1, 2, 4, 2, 3, 4, 3, 0, 4};

        /* Setup the vertex arrays and layouts for the pyramid */
        VertexArray pyramidArray;
        VertexBuffer pyramidBuffer;
        /* Generates an element array buffer object and links to the indices we
         * are using*/
        IndexBuffer pyramidIndices;
        /* Produce the pyramidLayout of the vertex array object so we know how
         * to decode our list of floats! */
        VertexBufferLayout pyramidLayout;

    public:
        Pyramid(float x=0, float y=0, float z=0);
        ~Pyramid();
        void bind() const override;
        void unbind() const override;
        const VertexArray& getVertexArray() const override {
            return pyramidArray;
        }
        const IndexBuffer& getIndexBuffer() const override {
            return pyramidIndices;
        }
};

}  // namespace vobo
#endif  //_pyramid_h_ header