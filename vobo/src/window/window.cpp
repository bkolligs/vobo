#include "window.h"

namespace vobo {

void GLAPIENTRY errorCallback(GLenum source, GLenum type, GLuint id,
                              GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam) {
    handleErrorDisplay(source, type, id, severity, length, message, userParam);
}

Window::Window(int width, int height, bool verbose, bool debug)
    : windowWidth_{width},
      windowHeight_{height},
      verbose_{verbose},
      debug_{debug} {
    int result = initialize();
}
Window::~Window() {
    /* Destroy the window object */
    glfwDestroyWindow(window_);
    glfwTerminate();
}

int Window::initialize() {
    // Initialize GLFW so we can use the following functions
    if (!glfwInit()) {
        VOBO_ERROR_LOG("Failed to initialize GLFW");
        return -1;
    }

    verbose_ and VOBO_DEBUG_LOG("Initialized GLFW");

    /* Enable the Debug context for GLFW */
    if (debug_) glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    /* Set up anti-aliasing */
    glfwWindowHint(GLFW_SAMPLES, 4);
    /* Create a windowed mode window and its OpenGL context */
    window_ = glfwCreateWindow(windowWidth_, windowHeight_,
                               mainWindowName_.c_str(), NULL, NULL);
    if (!window_) {
        VOBO_ERROR_LOG("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    /* Make the window_'s context current */
    glfwMakeContextCurrent(window_);
    /* Set the swap interval to be in line with our monitor refresh rate */
    glfwSwapInterval(1);

    /* Actually load the OpenGL specified functions with GLEW */
    // if (glewInit() != GLEW_OK) {
    //     VOBO_ERROR_LOG("Could not load GLEW!");
    //     return -1;
    // }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        VOBO_ERROR_LOG("Could not load OpenGL!");
        return -1;
    }
    /* Set the viewport to default to size of window */
    glViewport(0, 0, windowWidth_, windowHeight_);

    /* Initialize the window events and inputs callbacks */
    int result = events.initialize(window_);

    /* Enable the error callback */
    if (debug_) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(errorCallback, 0);
    }

    verbose_ and VOBO_DEBUG_LOG("Loaded OpenGL! "
                                << "Using OpenGL configuration: "
                                << "\n\tVersion: " << glGetString(GL_VERSION)
                                << "\n\tVendor: " << glGetString(GL_VENDOR)
                                << "\n\tDevice: " << glGetString(GL_RENDERER));

    return 0;
}

int Window::open() {
    /* generate a buffer to store the pyramidVertices of the triangle */
    float pyramidVertices[] = {
        -0.5f, 0.0f,  0.5f, 0.1f,  0.0f,  0.02f, -0.5f, 0.0f,  -0.5f, 0.8f,
        0.3f,  0.02f, 0.5f, 0.0f,  -0.5f, 0.2f,  0.8f,  0.12f, 0.5f,  0.0f,
        0.5f,  0.8f,  0.3f, 0.02f, 0.0f,  0.8f,  0.0f,  0.1f,  0.1f,  0.92f,
    };

    uint pyramidData[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

    /* Vertex buffer to hold the square */
    float squareVertices[] = {-0.5, -0.5, 0.0,  0.0, 0.0, -0.5, 0.5,
                              0.0,  0.0,  1.0,  0.5, 0.5, 0.0,  1.0,
                              1.0,  0.5,  -0.5, 0.0, 1.0, 0.0};
    uint squareIndices[]   = {0, 1, 2, 0, 2, 3};

    VertexBuffer squareBuffer(squareVertices, sizeof(squareVertices));
    VertexBufferLayout squareLayout;
    squareLayout.push<float>(3, "positions");
    squareLayout.push<float>(2, "texture_coords");
    VertexArray squareArray(debug_);
    IndexBuffer squareIB(squareIndices,
                         sizeof(squareIndices) / sizeof(unsigned int));
    /* Associate the array with the buffers */
    squareArray.bind();
    squareBuffer.bind();
    squareArray.linkVBO(squareBuffer, squareLayout);

    /* generate a vertex array and bind it */
    VertexArray pyramid(debug_);
    pyramid.bind();

    VertexBuffer pyramidBuffer(pyramidVertices, sizeof(pyramidVertices));
    pyramidBuffer.bind();

    /* Generates an element array buffer object and links to the indices we are
     * using*/
    IndexBuffer pyramidIndices(pyramidData,
                               sizeof(pyramidData) / sizeof(unsigned int));

    /* Produce the pyramidLayout of the vertex array object so we know how to
     * decode our list of floats! */
    VertexBufferLayout pyramidLayout;
    /* We "push" a new type of data onto the pyramidLayout, so it can calculate
     * stride and offset automatically */
    pyramidLayout.push<float>(3, "positions");
    pyramidLayout.push<float>(3, "color");
    /* link the vertex array and buffer objects */
    pyramid.linkVBO(pyramidBuffer, pyramidLayout);

    /* Produce the shaders */
    Shader shaders(VOBO_SRC_DIR + "assets/shaders/pyramid.glsl", verbose_);
    Shader shadersFlat(VOBO_SRC_DIR + "assets/shaders/square.glsl", verbose_);

    // /* Handle the texture here */
    Texture checkerboard(VOBO_SRC_DIR + "assets/textures/checkerboard.png");
    checkerboard.bind(0);

    /* Unbind to prevent accidental modifications */
    pyramid.unbind();
    pyramidBuffer.unbind();
    pyramidIndices.unbind();

    /* Create a renderer class */
    Renderer renderer;
    /* Set the camera controller */
    PerspectiveController cameraController(events, 60, windowWidth_, windowHeight_);
    /* Loop until the user closes the window_ */
    while (events.show()) {
        renderer.clear(
            {159.0f / 255.0f, 195.0f / 255.0f, 252.0f / 255.0f, 0.1});
        renderer.beginScene();

        /* Set the uniform to the texture slot */
        renderer.draw(squareArray, squareIB, shadersFlat);
        // shadersFlat.setUniformInt("uTexture", 0);
        // model pose matrix
        glm::mat4 model = glm::mat4(1.0f);
        // camera extrinsics matrix
        glm::mat4 view = glm::mat4(1.0f);
        // projection intrinsics matrix
        glm::mat4 proj = glm::mat4(1.0f);
        renderer.draw(pyramid, pyramidIndices, shaders);
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f));
        model = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        shaders.setUniformMat4F("uModel", model);
        shaders.setUniformMat4F("uViewProjection", cameraController.getCamera().getViewProjection());

        cameraController.onUpdate();

        renderer.endScene();
        onUpdate();
    }

    return 0;
}

void Window::onUpdate() {
        /* Swap front and back buffers */
        glfwSwapBuffers(window_);

        /* Poll for and process events */
        glfwPollEvents();
}

}  // namespace vobo