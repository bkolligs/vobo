#include "renderer.h"

namespace vobo {

Renderer::Renderer(/* args */) {
    /* Enable depth testing so that OpenGL renders far away vertices behind
     * closer ones */
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {}

void Renderer::clear(const std::array<float, 4> backgroundColor) {
    /* Specify the color of the background */
    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2],
                 backgroundColor[4]);
    /* Render here clear the depth buffer bit and the color bit*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::draw(const MeshObject* object, Shader& shader) const {
    if (object && pSceneCamera_) {
        object->bind();
        shader.bind();
        /* Set the model matrix from the object */
        shader.setUniformMat4F("uModel", object->getModelMatrix());
        shader.setUniformMat4F("uViewProjection", pSceneCamera_->getViewProjection());
        /* Load any other object specific uniforms into the shader */
        object->modifyShader(shader);

        /* Draw elements */
        glDrawElements(GL_TRIANGLES, object->getIndexBuffer().getCount(),
                       GL_UNSIGNED_INT, nullptr);
    } else
    {
        if (not object) throw std::runtime_error("[Renderer] MeshObject Pointer is Null!");
        else if (not pSceneCamera_) throw std::runtime_error("[Renderer] SceneCamera Pointer is Null");
    }
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& eb,
                    const Shader& shader) const {
    /* Bind the buffer objects to send to the GPU before drawing */
    va.bind();
    eb.bind();
    shader.bind();
    /* Draw elements */
    glDrawElements(GL_TRIANGLES, eb.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::beginScene(const PerspectiveCamera & camera) {
    /* Assign the pointer to the scene for now */
    pSceneCamera_ = &camera;
}

void Renderer::submit() {}

void Renderer::endScene() {}

}  // namespace vobo