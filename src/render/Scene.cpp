#include "Scene.h"
#include "../uniform/Object.h"

#include <GL/glew.h>
#include <GL/glx.h>

#include "../gl/disable.h"
#include "../gl/matrixMode.h"
        
void drawQuad() 
{
    glColor4f(1, 1, 1, 1);
    
    // Desenha imagem do PBO
    gl::Disable(GL_DEPTH_TEST);

    gl::MatrixMode(GL_PROJECTION);    
    glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);

    gl::MatrixMode(GL_MODELVIEW);

    // Desenha um quad de textura.
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1, 0);
    glVertex2f(1, 1);
    glVertex2f(0, 1);
    glEnd();

}

void render(const Scene& scene, glm::vec3 lightPos) 
{   
    //Load program
    
    drawQuad();    
    
//    for(const auto& obj : scene.objects())
//        uniform::load(obj);
    
    //Unload program
}

