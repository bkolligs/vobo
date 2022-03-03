#include "main_window.h"

void GLAPIENTRY errorCallback(GLenum source, GLenum type, GLuint id,
                              GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam) {
    handleErrorDisplay(source, type, id, severity, length, message, userParam);
}

MainWindow::MainWindow(int width, int height, bool verbose, bool debug)
    : window_width_{width}, window_height_{height}, verbose_{verbose}, debug_{debug} {
    int result = initialize();
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

    /* Actually load the OpenGL specified functions with GLEW */
    if (glewInit() != GLEW_OK) {
        std::cerr << ERROR_INFO("Could not load GLEW!") << std::endl;
        return -1;
    }

    /* Enable the error callback */
    
    if (debug_){
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
        -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f,  // Lower left corner
        0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f,  // Lower right corner
        0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f,  // Inner left
        0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f,  // Inner right
        0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f   // Inner down
    };

    uint indices[] = {
        0, 3, 5,  // lower left triangle
        3, 2, 4,  // lower right triangle
        5, 4, 1   // upper triangle
    };

    /* generate a vertex array and bind it */
    VAO vao1;
    vao1.bind();

    VBO vbo1(vertices, sizeof(vertices));
    vbo1.bind();

    /* Generates an element array buffer object and links to indices */
    EBO ebo1(indices, sizeof(indices));

    /* link the vertex array and buffer objects */
    vao1.linkVBO(vbo1, 0);

    /* Produce the shaders */
    ShaderLoader shaders("../src/shaders.shader");

    /* Unbind to prevent accidental modifications */
    vao1.unbind();
    vbo1.unbind();
    ebo1.unbind();

    /* Loop until the user closes the window_ */
    while (!glfwWindowShouldClose(window_)) {
        /* Specify the color of the background */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // glUseProgram(shaderProgram);
        shaders.activate();
        /* bind the vertex array object so we use it, otherwise we get a
         * SegFault*/
        vao1.bind();
        /* draw the triangles */
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window_);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shaders.free();
    vao1.free();
    vbo1.free();
    ebo1.free();

    /* Destroy the window object */
    glfwDestroyWindow(window_);
    glfwTerminate();
    return 0;
}

/**
 * compile a shader
 */
static uint compileShader(const std::string& source, uint type) {
    uint id = glCreateShader(type);
    const char* src = source.c_str();
    /* specify the source of shader */
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        // retrieve the information from opengl
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        /* weird casting from the Cherno */

        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}
/**
 * Read in the source code of a shader
 */
static int createShader(const std::string& vertexShader,
                        const std::string& fragmentShader) {
    /* produce a program ID */
    uint program = glCreateProgram();
    uint vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    uint fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    /* Link the shader source code and validate it */
    glLinkProgram(program);
    glValidateProgram(program);

    /* delete the shaders */
    glDeleteShader(vs);
    glDeleteShader(fs);

    /* Should detach the shaders here */
    // glDetachShader(program, vs);
    // glDetachShader(program, fs);
    return 0;
}