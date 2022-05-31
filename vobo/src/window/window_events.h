#ifndef _window_events_h_
#define _window_events_h_
#include "GLFW/glfw3.h"
#include "log.h"
#include "vobo_pch.h"

namespace vobo {

enum class ScrollAction { BACKWARDS = -1, NONE, FORWARDS };

enum class CharState { INPUT, NONE };

/**
 * This is a class for polling inputs
 */
class WindowInputs {
    private:
        /* In case we store other non-mouse data lets store it together */
        struct MouseData {
                double scrollX = 0, scrollY = 0;
                double xPos = 0, yPos = 0;
                double xVel = 0, yVel = 0;
                ScrollAction scrollState = ScrollAction::NONE;
        };

        MouseData mouse_;

        std::stringstream charData_;
        CharState charState_;

    public:
        /* Dealing with mouse data */
        void setMousePos(double xPos, double yPos);
        double getMouseX() { return mouse_.xPos; }
        double getMouseY() { return mouse_.yPos; }
        double getMouseXVel() { return mouse_.xVel; }
        double getMouseYVel() { return mouse_.yVel; }
        void setScrollY(double yOffset);
        const int getScrollY();

        /* Query a keycode */
        const bool isKeyPressed(GLFWwindow* window, int keycode);
        /* Query a mouse button */
        const bool isMousePressed(GLFWwindow* window, int button);

        /* Handle the text input case */
        void inputCharsToStream(char character);
        const std::string getInputStr();
};

class WindowEvents {
    private:
        GLFWwindow* window_ = nullptr;

    public:
        WindowInputs inputs;
        WindowEvents();
        ~WindowEvents();
        int initialize(GLFWwindow* window);
        /* Provide some indirection for the input accessors */
        int getScrollY() { return inputs.getScrollY(); }
        bool isKeyPressed(int keycode) {
            return inputs.isKeyPressed(window_, keycode);
        }
        bool isMousePressed(int button) {
            return inputs.isMousePressed(window_, button);
        }
        double getMouseX() { return inputs.getMouseX(); }
        double getMouseY() { return inputs.getMouseY(); }
        double getMouseXVel() { return inputs.getMouseXVel(); }
        double getMouseYVel() { return inputs.getMouseYVel(); }
        bool showWindow() {
            if (window_)
                return not glfwWindowShouldClose(window_);
            else
                throw std::runtime_error("[Inputs] Window pointer is null!");
        }
};

}  // namespace vobo
#endif  //_window_events_h_ header