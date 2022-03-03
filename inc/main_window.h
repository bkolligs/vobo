#ifndef _main_window_h_
#define _main_window_h_

#include "colored_output_strings.h"
#include <iostream>

// include GLEW which allows us to access the modern GL
#include <GL/glew.h>
// GLFW focuses on opening a window on the OS
#include <GLFW/glfw3.h>
// GLM contains math functions we will use
#include <glm/glm.hpp>
// custom abstractions
#include "ebo.h"
#include "shader_loader.h"
#include "vao.h"
#include "vbo.h"

class MainWindow {
   private:
    GLFWwindow* window_;
    int window_width_;
    int window_height_;
    bool verbose_;
    std::string main_window_name = "Oculobo 2022v0.1";

   public:
    MainWindow(int width = 640, int height = 480, bool verbose = true);
    /**
     * Opens a window
     */
    int open(void);
    /**
     * Initializes GLFW
     */
    int initialize(void);
};

static uint compileShader(const std::string& source, uint type);
static int createShader(const std::string& vertexShader,
                        const std::string& fragmentShader);
#endif  //_main_window_h_ header