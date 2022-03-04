#include "main_window.h"

void GLAPIENTRY errorCallback(GLenum source, GLenum type, GLuint id,
                              GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam) {
    handleErrorDisplay(source, type, id, severity, length, message, userParam);
}

MainWindow::MainWindow(int width, int height, bool verbose, bool debug)
    : window_width_{width},
      window_height_{height},
      verbose_{verbose},
      debug_{debug} {
    int result = initialize();
}
MainWindow::~MainWindow() {
    /* Destroy the window object */
    glfwDestroyWindow(window_);
    glfwTerminate();
}

int MainWindow::initialize() {
    // Initialize GLFW so we can use the following functions
    if (!glfwInit()) {
        std::cerr << ERROR_INFO("Failed to initialize GLFW") << std::endl;
        return -1;
    }

    verbose_ and std::cout << SUCCESS_INFO("Initialized GLFW") << std::endl;

    /* Enable the Debug context for GLFW */
    if (debug_) glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    /* Set up anti-aliasing */
    glfwWindowHint(GLFW_SAMPLES, 4);
    /* Create a windowed mode window and its OpenGL context */
    window_ = glfwCreateWindow(window_width_, window_height_,
                               main_window_name_.c_str(), NULL, NULL);
    if (!window_) {
        std::cerr << ERROR_INFO("Failed to create GLFW window") << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window_'s context current */
    glfwMakeContextCurrent(window_);
    /* Set the swap interval to be in line with our monitor refresh rate */
    glfwSwapInterval(1);

    /* Actually load the OpenGL specified functions with GLEW */
    if (glewInit() != GLEW_OK) {
        std::cerr << ERROR_INFO("Could not load GLEW!") << std::endl;
        return -1;
    }

    /* Enable the error callback */

    if (debug_) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(errorCallback, 0);
    }

    verbose_ and std::cout << SUCCESS_INFO("Initialized OpenGL") << std::endl
                           << "Using OpenGL version: "
                           << glGetString(GL_VERSION) << std::endl;

    return 0;
}

int MainWindow::open() {
    /* generate a buffer to store the vertices of the triangle */
    float vertices[] = {
        -0.5f, 0.0f,  0.5f,  0.1f, 0.0f, 0.02f, 
        -0.5f, 0.0f, -0.5f,  0.8f, 0.3f, 0.02f, 
         0.5f, 0.0f, -0.5f,  0.2f, 0.8f, 0.12f, 
         0.5f, 0.0f,  0.5f,  0.8f, 0.3f, 0.02f, 
         0.0f, 0.8f,  0.0f,  0.1f, 0.1f, 0.92f, 
    };

    uint indices[] = {
        0, 1, 2,  
        0, 2, 3,  
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    /* generate a vertex array and bind it */
    VertexArray vao1(debug_);
    vao1.bind();


    VertexBuffer vbo1(vertices, sizeof(vertices));
    vbo1.bind();

    /* Generates an element array buffer object and links to the indices we are using*/
    ElementBuffer ebo1(indices, 18);

    /* Produce the layout of the vertex array object so we know how to decode our list of floats! */
    VertexBufferLayout layout;
    /* We "push" a new type of data onto the layout, so it can calculate stride and offset automatically */ 
    layout.push<float>(3, "positions");
    layout.push<float>(3, "color");
    /* link the vertex array and buffer objects */
    vao1.linkVBO(vbo1, layout);

    /* Produce the shaders */
    Shader shaders("../src/assets/shaders/shaders.shader", verbose_);

    /* Unbind to prevent accidental modifications */
    vao1.unbind();
    vbo1.unbind();
    ebo1.unbind();

    /* Make a nice animation for the triangles */
    float r = 0.0;
    float increment = 0.01f;

    /* Create a renderer class */
    Renderer renderer;

    /* Loop until the user closes the window_ */
    while (!glfwWindowShouldClose(window_)) {
        renderer.clear({159.0f/255.0f, 195.0f/255.0f, 252.0f/255.0f, 0.1});

        /* Render something to the screen! */
        renderer.draw(vao1, ebo1, shaders);
        /* Should use a material here instead of this, add this later */
        // shaders.setUniform4F("uColor", r, 0.4f, 0.1f, 0.5f);
        // model pose matrix
        glm::mat4 model = glm::mat4(1.0f);
        // camera extrinsics matrix
        glm::mat4 view = glm::mat4(1.0f);
        // projection intrinsics matrix
        glm::mat4 proj = glm::mat4(1.0f);
        model = glm::rotate(model, r, glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        view = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        proj = glm::perspective(glm::radians(60.0f), (float) window_width_/window_height_, 0.1f, 100.0f);


		shaders.setUniformMat4F("uModel", model);
		shaders.setUniformMat4F("uView", view);
		shaders.setUniformMat4F("uProj", proj);
        // shaders.setUniform1F("uScale", -0.5);
        if (r > 360.0f)
            increment = -0.01f;
        else if (r < 0.0f)
            increment = 0.01f;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window_);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}