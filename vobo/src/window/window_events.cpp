#include "window_events.h"

namespace vobo {

WindowEvents::WindowEvents() {}

int WindowEvents::initialize(GLFWwindow* window) {
    /* Check the pointer is not null */
    if (window) {
		window_ = window;
        /* Set the window pointer to our input data */
        glfwSetWindowUserPointer(window_, &inputs);

        /* Bind all the callback functions */
        glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button,
                                               int action, int mods) {
            double xPos, yPos;
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                glfwGetCursorPos(window, &xPos, &yPos);
                VOBO_DEBUG_LOG("Pressed the left mouse button! Pressed at: ("
                               << xPos << "," << yPos << ")");
            }
        });

        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key,
                                       int scancode, int action, int mods) {
            VOBO_DEBUG_LOG("Window recieved the following key: " << key);
        });

        glfwSetCursorPosCallback(window_, [](GLFWwindow * window, double xPos, double yPos) {
			VOBO_DEBUG_LOG("mouse at " << xPos << ", " << yPos);

        });

        glfwSetScrollCallback(
            window_, [](GLFWwindow* window, double xOffset, double yOffset) {
                WindowInputs* data =
                    (WindowInputs*)glfwGetWindowUserPointer(window);
                data->setScrollY(yOffset);
            });
		return 0;
    }
	return -1;
}

WindowEvents::~WindowEvents() {}

}  // namespace vobo