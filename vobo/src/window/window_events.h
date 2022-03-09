#ifndef _window_events_h_
#define _window_events_h_
#include "GLFW/glfw3.h"
#include "vobo_pch.h"
#include "log.h"

namespace vobo
{
	enum class ScrollAction {
    BACKWARDS=-1,
    NONE,
    FORWARDS
};

struct WindowInputs
{
    /* For dealing with scrolling */
    double scrollX=0, scrollY=0, lastScrollX =0 , lastScrollY=0;
    ScrollAction state = ScrollAction::NONE;

    /* Dealing with mouse data */

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

class WindowEvents {
   private:
    GLFWwindow* window_;

   public:
	WindowInputs inputs;
    WindowEvents();
    ~WindowEvents();
    int initialize(GLFWwindow * window);
};



} // namespace vobo
#endif  //_window_events_h_ header