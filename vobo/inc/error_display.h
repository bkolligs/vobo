#ifndef _error_h_
#define _error_h_

#include <iostream>
#include "log.h"
#include <GL/glew.h>

void handleErrorDisplay(GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei length, const GLchar* message,
                        const void* userParam);

#endif  //_error_h_ header