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
#include "index_buffer.h"
#include "error_display.h"
#include "renderer.h"
#include "shader.h"
#include "log.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "texture.h"
#include "orthographic_camera.h"
#include "perspective_camera.h"


namespace vobo
{

enum class ScrollAction {
    BACKWARDS=-1,
    NONE,
    FORWARDS
};

struct WindowInputs
{
    double scrollX=0, scrollY=0, lastScrollX =0 , lastScrollY=0;
    ScrollAction state = ScrollAction::NONE;

	void setScrollY(double yOffset) {
        /* Set the current scroll wheel state */
        if (yOffset == -1 )
            state = ScrollAction::FORWARDS;
        else if (yOffset == 1)
            state = ScrollAction::BACKWARDS;
    }

    int getScrollY(){
        int output = 0;
        if (state == ScrollAction::FORWARDS)
            output = 1;
        else if (state == ScrollAction::BACKWARDS)
            output = -1;
        /* Reset the state */
        state = ScrollAction::NONE;
        return output;
    }
    
};
    

class Window {
   private:
    GLFWwindow* window_;
    int windowWidth_;
    int windowHeight_;
    /* Interactivity flags */
    bool verbose_;
    bool debug_;
    std::string main_window_name_ = "Oculobo 2022v0.1";

   public:
    WindowInputs windowData;
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
};

} // namespace vobo
#endif  //_vobo_window_h_ header