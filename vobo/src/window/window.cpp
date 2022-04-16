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
    if (vSync_) glfwSwapInterval(1);

    /* Actually load the OpenGL specified functions with GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
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
    /* Produce the shaders */
    Shader shaders(VOBO_SRC_DIR + "assets/shaders/pyramid.glsl", verbose_);

    /* Create a renderer class */
    Renderer renderer;
    /* Set the camera controller */
    PerspectiveController cameraController(events, 60, windowWidth_,
                                           windowHeight_);
    Pyramid testPyramid(2.0f, 0.0f, 0.0f);
    testPyramid.scale(1.0, 1.0, 1.0);
    Cube testCube(0.0f, 0.0f, -0.0f);
    // IcoSphere testSphere;
    /* Loop until the user closes the window_ */
    while (events.showWindow()) {
        renderer.clear(
            {159.0f / 255.0f, 195.0f / 255.0f, 252.0f / 255.0f, 0.1});
        renderer.beginScene(cameraController.getCamera());

        testCube.scale(1.0, 1.000, 1.01);

        renderer.draw(&testPyramid, shaders);
        renderer.draw(&testCube, shaders);
        // renderer.draw(&testSphere, shaders);

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