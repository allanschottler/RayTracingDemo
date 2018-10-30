#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#include "model/Scene.h"
#include "render/Scene.h"
#include "model/Object.h"

#include <iostream>

/***************************************/
/*      GLOBALS                        */
/***************************************/
std::vector<Object> g_objs
    { Sphere({0, 0, 0}) };
    
Scene* g_scene = nullptr;

glm::vec3 g_lightPos{1, 1, 1};

/***************************************/
/*      GL INIT                        */
/***************************************/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    render(*g_scene);
    glFlush();
}

void init(Camera cam) 
{    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    if(g_scene) delete g_scene;
    
    
    g_scene = new Scene(std::move(cam), g_objs, g_lightPos);
}

int main(int argc, char** argv)
{ 
    glm::vec2 viewport{800, 600};
    
    Camera cam {
        glm::lookAt({0, -3, 2}, {0, 0, 0}, {0, 1, 0}),
        glm::perspective(40, viewport.x/viewport.y, 0.1f, 100.f),
        viewport
    };
    
    // GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(viewport.x, viewport.y); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dojo Raytracing");
    
    // GLEW
    glewInit();
    
    // App
    init();
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}
