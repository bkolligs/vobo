#include "event_handler.h"

namespace vobo
{

EventHandler::EventHandler(GLFWwindow* window) : window_{window} {
	/* Bind all the callback functions */
	glfwSetMouseButtonCallback(window_, [](GLFWwindow * window, int button, int action, int mods){}) ;
	glfwSetCursorPosCallback(window_, EventHandler::cursorPosCallback);
	glfwSetScrollCallback(window, EventHandler::scrollCallback);

}

void EventHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}
void EventHandler::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
}
void EventHandler::scrollCallback(GLFWwindow * window, double xOffset, double yOffset) {

}

EventHandler::~EventHandler() {}

} // namespace vobo