#include "DebugMessage.h"
#include <functional>

namespace gl {

void MessageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, 
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, 
            severity, 
            message);
}

DebugMessage::DebugMessage()
    : _debug_output(GL_DEBUG_OUTPUT)
{
    glDebugMessageCallback((GLDEBUGPROC)MessageCallback, 0);
}

}
