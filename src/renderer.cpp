#include "renderer.h"

Renderer::Renderer(/* args */)
{
	/* Enable depth testing so that OpenGL renders far away vertices behind closer ones */
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
}

void Renderer::clear(const std::array<float, 4> backgroundColor) {
	/* Specify the color of the background */
	glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[4]);
	/* Render here clear the depth buffer bit and the color bit*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader) const {
	/* Bind the buffer objects to send to the GPU before drawing */
	va.bind();
	eb.bind();
	shader.bind();
	/* Draw elements */
	glDrawElements(GL_TRIANGLES, eb.getCount(), GL_UNSIGNED_INT, nullptr);

}