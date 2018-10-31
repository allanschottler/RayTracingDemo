#pragma once

namespace gl
{
    struct Disable
    {
        Disable(GLuint mode)
            : _mode(mode)
        { glDisable(mode); }
        
        ~Disable()
        { glEnable(_mode); }
        
    private:
        GLuint _mode;
    };
}