#include "error_display.h"

void handleErrorDisplay(GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei length, const GLchar* message,
                        const void* userParam) {
    std::string _source, _type, _severity;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            _source = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "WINDOW SYSTEM";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "SHADER COMPILER";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "THIRD PARTY";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "APPLICATION";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            _source = "UNKNOWN";
            break;

        default:
            _source = "UNKNOWN";
            break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            _type = "ERROR";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "DEPRECATED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "UDEFINED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_OTHER:
            _type = "OTHER";
            break;

        case GL_DEBUG_TYPE_MARKER:
            _type = "MARKER";
            break;

        default:
            _type = "UNKNOWN";
            break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            _severity = RED_BOLD_STRING("HIGH");
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            _severity = YELLOW_BOLD_STRING("MEDIUM");
            break;

        case GL_DEBUG_SEVERITY_LOW:
            _severity = MAGENTA_BOLD_STRING("LOW");
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            _severity = GREEN_BOLD_STRING("NOTIFICATION");
            break;

        default:
            _severity = "UNKNOWN";
            break;
    }
    VOBO_WARNING_LOG("\n\tSource: " << _source << "\n\tType:" << _type
                                    << "\n\tID: " << id
                                    << "\n\tSeverity: " << _severity
                                    << "\n\tMessage: \n\t" << message);
}