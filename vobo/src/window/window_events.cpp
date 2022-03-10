#include "window_events.h"

namespace vobo {

void WindowInputs::setScrollY(double yOffset) {
    /* Set the current scroll wheel state */
    if (yOffset == -1)
        mouse_.scrollState = ScrollAction::FORWARDS;
    else if (yOffset == 1)
        mouse_.scrollState = ScrollAction::BACKWARDS;
}
void WindowInputs::setMousePos(double xPos, double yPos) {
    /* Calculate mouse velocity using last position */
    mouse_.xVel = xPos - mouse_.xPos;
    mouse_.yVel = yPos - mouse_.yPos;
    /* Update current position */
    mouse_.xPos = xPos;
    mouse_.yPos = yPos;
}

const int WindowInputs::getScrollY() {
    /* Get the current scroll state and cast to an int */
    int output = (int)mouse_.scrollState;
    /* Reset the state */
    mouse_.scrollState = ScrollAction::NONE;
    return output;
}

const bool WindowInputs::isKeyPressed(GLFWwindow* window, int keycode) {
    if (window) {
        int state = glfwGetKey(window, keycode);
        if (state == GLFW_PRESS) return true;
        return false;
    } else
        throw std::runtime_error(
            VOBO_CRITICAL_STRING("[Inputs] Window pointer is null!"));
}

const bool WindowInputs::isMousePressed(GLFWwindow* window, int button) {
    if (window) {
        int state = glfwGetMouseButton(window, button);
        if (state == GLFW_PRESS) return true;
        return false;
    } else
        throw std::runtime_error(
            VOBO_CRITICAL_STRING("[Inputs] Window pointer is null!"));
}

void WindowInputs::inputCharsToStream(char character) {
    charState_ = CharState::INPUT;
    charData_ << character;
}
const std::string WindowInputs::getInputStr() {
    std::string output = charData_.str();
    /* Clear the input stream and reset it's state */
    charData_.str("");
    charState_ = CharState::NONE;
    return output;
}

WindowEvents::WindowEvents() {}

int WindowEvents::initialize(GLFWwindow* window) {
    /* Check the pointer is not null */
    if (window) {
        window_ = window;
        /* Set the window pointer to our input data */
        glfwSetWindowUserPointer(window_, &inputs);

        /* Bind all the callback functions */
        glfwSetMouseButtonCallback(
            window_, [](GLFWwindow* window, int button, int action, int mods) {
                /* Will use this later for interaction */
            });

        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key,
                                       int scancode, int action, int mods) {
            /* Not sure yet what to do here */
        });

        glfwSetCursorPosCallback(
            window_, [](GLFWwindow* window, double xPos, double yPos) {
                WindowInputs* data =
                    (WindowInputs*)glfwGetWindowUserPointer(window);
                data->setMousePos(xPos, yPos);
            });

        glfwSetScrollCallback(
            window_, [](GLFWwindow* window, double xOffset, double yOffset) {
                WindowInputs* data =
                    (WindowInputs*)glfwGetWindowUserPointer(window);
                data->setScrollY(yOffset);
            });
        glfwSetCharCallback(window_,
                            [](GLFWwindow* window, unsigned int codepoint) {
                                VOBO_INFO_LOG((char)codepoint);
                            });
        return 0;
    }
    return -1;
}

WindowEvents::~WindowEvents() {}

}  // namespace vobo