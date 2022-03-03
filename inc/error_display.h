#ifndef _error_h_
#define _error_h_

#include "colored_output_strings.h"
#include <GL/glew.h>
#include <iostream>

void handleErrorDisplay(GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei length, const GLchar* message,
                        const void* userParam);

#endif  //_error_h_ header