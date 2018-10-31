#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <freijo/enable.hpp>

namespace gl {

struct DebugMessage {
    DebugMessage();
private:
    freijo::enable _debug_output;
};

}
