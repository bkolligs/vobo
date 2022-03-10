#ifndef _vobo_window_h_
#define _vobo_window_h_

// include GLEW which allows us to access the modern GL
#include <GL/glew.h>
// GLFW focuses on opening a window on the OS
#include <GLFW/glfw3.h>
// precompiled headers and common types
#include "core.h"
#include "stb_image.h"
// custom abstractions
#include "error_display.h"
#include "index_buffer.h"
#include "log.h"
#include "orthographic_camera.h"
#include "perspective_camera.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "window_events.h"

namespace vobo {

class Window {
    private:
        GLFWwindow* window_ = nullptr;
        int windowWidth_;
        int windowHeight_;
        /* Interactivity flags */
        bool verbose_;
        bool debug_;
        std::string mainWindowName_ = "Oculobo 2022v0.1";

    public:
    	WindowEvents events;
        Window(int width = 640, int height = 480, bool verbose = true,
               bool debug = true);
        ~Window();
        /**
         * Opens a window
         */
        int open(void);
        /**
         * Initializes GLFW
         */
        int initialize(void);
        /**
         * On Update
         */
        void onUpdate();
};

}  // namespace vobo
#endif  //_vobo_window_h_ header