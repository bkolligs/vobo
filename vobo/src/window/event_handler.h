#ifndef _event_handler_h_
#define _event_handler_h_
#include "GLFW/glfw3.h"
#include "vobo_pch.h"

namespace vobo
{
	

struct EventHandlerData {
	double mouseX, mouseY; 
	double mouseXVelocity, mouseYVelocity;
	double mouseXPosLast, mouseYPosLast;
};

class EventHandler {
   private:
    GLFWwindow* window_;

   public:
	EventHandlerData data;
    EventHandler(GLFWwindow* window);
    ~EventHandler();
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
};



} // namespace vobo
#endif  //_event_handler_h_ header