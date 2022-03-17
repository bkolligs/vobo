#ifndef _cube_h_
#define _cube_h_

#include "vobo_pch.h"
#include "mesh_object.h"

namespace vobo
{

struct CubeVertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoords;
};

	
class Cube : public MeshObject {
	private:
	/* Add a vector of the vertices we are using */
	std::vector<CubeVertex> vertices{
		/* Vertex 1 */
		{ .position={-0.5f, -0.5f, 0.5f},
			.color={0.0f, 0.0f, 1.0f},
			.texCoords={0.0f, 0.0f}},
		/* Vertex 2 */
		{ .position={0.5f, -0.5f, 0.5f},
			.color={1.0f, 0.0f, 1.0f},
			.texCoords={0.5f, 0.0f}},
		/* Vertex 3 */
		{ .position={0.5f, -0.5f, -0.5f},
			.color={1.0f, 0.0f, 0.0f},
			.texCoords={0.5f, 0.5f}},
		/* Vertex 4 */
		{ .position={-0.5f, -0.5f, -0.5f},
			.color={0.0f, 0.0f, 0.0f},
			.texCoords={0.5f, -0.5f}},
		/* Vertex 5 */
		{ .position={-0.5f, 0.5f, 0.5f},
			.color={0.0f, 1.0f, 1.0f},
			.texCoords={0.0f, 0.5f}},
		/* Vertex 6 */
		{ .position={0.5f, 0.5f, 0.5f},
			.color={1.0f, 1.0f, 1.0f},
			.texCoords={0.0f, -0.5f}},
		/* Vertex 7 */
		{ .position={0.5f, 0.5f, -0.5f},
			.color={1.0f, 1.0f, 0.0f},
			.texCoords={-0.5f, 0.5f}},
		/* Vertex 8 */
		{ .position={-0.5f, 0.5f, -0.5f},
			.color={0.0f, 1.0f, 0.0f},
			.texCoords={1.0f, 1.0f}},
	};
	uint cubeData[3*12] = {
		/* Face 1 */
		1, 2, 5,
		5, 6, 2,
		/* Face 2 */
		8, 4, 7,
		7, 4, 3,
		/* Face 3 */
		2, 7, 3,
		2, 7, 6,
		/* Face 4 */
		1, 6, 5,
		5, 6, 8,
		/* Face 5 */
		5, 6, 8, 
		6, 7, 8,
		/* Face 6 */
		1, 2, 4, 
		2, 3, 4
	};

	/* Setup the vertex arrays and layouts for the cube */
	VertexArray cubeArray;
	VertexBuffer cubeBuffer;
	/* Generates an element array buffer object and links to the indices we
		* are using*/
	IndexBuffer cubeIndices;
	/* Produce the layout of the vertex array object so we know how
		* to decode our list of floats! */
	VertexBufferLayout cubeLayout;

	public:
		Cube(float x =0, float y=0, float z=0);
		void bind() const override;
		void unbind() const override;
		bool modifyShader(Shader & shader) const override;
        virtual const VertexArray& getVertexArray() const override {
			return cubeArray;
		}
        virtual const IndexBuffer& getIndexBuffer() const override {
			return cubeIndices;
		}
};

} // namespace vobo
#endif //_cube_h_ header