#pragma once

namespace gl 
{
    struct MatrixMode
    {
        MatrixMode(GLuint mode)
        {
            glMatrixMode(mode);
            glPushMatrix();    
            glLoadIdentity();
        }
        
        ~MatrixMode()
        { glPopMatrix(); }
    };    
}
