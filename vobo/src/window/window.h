#ifndef _vobo_window_h_
#define _vobo_window_h_

#include "glad.h"
#include <GLFW/glfw3.h>
#include "core.h"
#include "error_display.h"
#include "log.h"
#include "perspective_controller.h"
#include "primitives.h"
#include "renderer.h"
#include "shader.h"
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
        bool vSync_                 = true;
        std::string mainWindowName_ = "Vobo 2022v0.1";
        WindowEvents events_;

    public:
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
        /* Set VSYNC */
        void setVSync(bool vSync) { vSync_ = vSync; }
        const WindowEvents & getEvents() const {return events_;}
};

}  // namespace vobo
#endif  //_vobo_window_h_ header