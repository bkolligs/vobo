#include "main_window.h"

MainWindow::MainWindow(int width, int height, bool verbose)
    : window_width_{width}, window_height_{height}, verbose_{verbose} {
    initialize();
}

int MainWindow::initialize() {
    // Initialize GLFW so we can use the following functions
    if (!glfwInit()) {
        std::cerr << ERROR_INFO("Failed to initialize GLFW") << std::endl;
        return -1;
    }

    verbose_ THEN_DO std::cout << SUCCESS_INFO("Initialized GLFW") << std::endl;

    /* Create a windowed mode window and its OpenGL context */
    window_ = glfwCreateWindow(window_width_, window_height_,
                               main_window_name.c_str(), NULL, NULL);
    if (!window_) {
        glfwTerminate();
        return -1;
    }

    /* Make the window_'s context current */
    glfwMakeContextCurrent(window_);

    if (glewInit() != GLEW_OK)
        std::cerr << ERROR_INFO("Could not load GLEW!") << std::endl;

    verbose_ THEN_DO std::cout << SUCCESS_INFO("Initialized GLEW") << std::endl << "Using OpenGL version: "<< glGetString(GL_VERSION) << std::endl;

    return 0;
}

int MainWindow::open() {
    /* generate a buffer to store the vertices of the triangle */
    float vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
    };

    uint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /* the buffer id */
    uint buffer;
    glGenBuffers(1, &buffer);
    /* select the buffer with bind */
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    /* place the vertices into the buffer */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /* Now we need to enable the vertex data */
    glEnableVertexAttribArray(0);
    /* Tell OpenGL what hte layout of this data is in this array*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);

	/* Reset the array buffer that is bound */
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Produce the shaders */
    ShaderLoader shaders("../src/shaders.shader");

    /* Loop until the user closes the window_ */
    while (!glfwWindowShouldClose(window_)) {
        /* Specify the color of the background */
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // glUseProgram(shaderProgram);
        shaders.activate();
        /* draw the triangles */
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window_);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // glDeleteProgram(shaderProgram);
    shaders.deactivate();

    return 0;
}

/**
 * compile a shader
 */
static uint compileShader(const std::string& source, uint type) {
    uint id = glCreateShader(type);
    const char * src = source.c_str();
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
        
        char * message= (char*) alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type==GL_VERTEX_SHADER ? "vertex" : "fragment") <<" shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}
/**
 * Read in the source code of a shader
 */
static int createShader(const std::string & vertexShader, const std::string& fragmentShader) {
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