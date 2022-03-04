#include "renderer.h"

Renderer::Renderer(/* args */)
{
}

Renderer::~Renderer()
{
}

void Renderer::clear(const std::array<float, 4> backgroundColor) {
	/* Specify the color of the background */
	glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[4]);
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader) const {
	/* Bind the buffer objects to send to the GPU before drawing */
	va.bind();
	eb.bind();
	shader.bind();
	/* Draw elements */
	glDrawElements(GL_TRIANGLES, eb.getCount(), GL_UNSIGNED_INT, nullptr);

}