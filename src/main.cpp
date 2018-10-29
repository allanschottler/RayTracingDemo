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
    {
        Sphere({0, 0, 0})
    };
    
Scene* g_scene = nullptr;

glm::vec3 g_lightPos{1, 1, 1};


/***************************************/
/*      GL INIT                        */
/***************************************/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    render(*g_scene, g_lightPos);
    glFlush();
}

void init (void) 
{    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    if(g_scene)
        delete g_scene;
    
    g_scene = new Scene(g_objs);
}

int main(int argc, char** argv)
{
    // GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); 
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
