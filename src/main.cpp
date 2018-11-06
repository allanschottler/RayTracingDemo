#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#include "model/Scene.h"
#include "render/Scene.h"
#include "model/Object.h"

#include "range/v3/all.hpp"
#include "detail/toUniqueObjs.h"
#include "detail/Arcball.h"
//#include "detail/loadScene.h"

#include <iostream>

/***************************************/
/*  GLOBALS                            */
/***************************************/

glm::vec4 viewport{0, 0, 800, 600};
glm::mat4 modelview{glm::lookAt(glm::vec3{0, 0, 5}, glm::vec3{0, 0, 0}, glm::vec3{0, 1, 0})};
glm::mat4 projection{glm::perspective(glm::radians(45.0f), viewport.z/viewport.w, 0.1f, 100.f)};

std::vector<object_t> g_objs{ 
    Camera {
        modelview,
        projection,
        viewport
    },
    Light({0, 0, 5}),
    Material(0.33f, 0.77f, {1, 0, 0, 1}, 1.f, 20.f),
    Plane({0, 0, -1}, {0, 0, 1}),
    Sphere({0, 0, 0}),
    Sphere({-3, -3, 0}),
    Sphere({0, -3, 0}),
    Sphere({3, -3, 0}),
    Sphere({-3, 0, 0}),
    Sphere({3, 0, 0}),
    Sphere({-3, 3, 0}),
    Sphere({0, 3, 0}),
    Sphere({3, 3, 0})
};    

Scene* g_scene = nullptr;

detail::Arcball arcball{modelview, projection, viewport};
    
/***************************************/
/*  GL INIT                            */
/***************************************/

void onMouse(int button, int state, int x, int y) 
{ arcball.onMouse(button, state, x, y); }

void onMotion(int x, int y) 
{ arcball.onMotion(x, y); }

void onIdle()
{
    if(arcball.onIdle(g_scene->transform))
        glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    render(*g_scene);
    glutSwapBuffers();
//    glFlush();
}
    
void init() 
{    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    if(g_scene) delete g_scene;    
    
    detail::UniqueIDs uniqueIds;
    auto uniqueObjs = detail::toUniqueObjs(g_objs, uniqueIds);
    g_scene = new Scene(std::move(uniqueObjs));
}    

int main(int argc, char** argv)
{    
    // GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(viewport.x, viewport.y);
    glutInitWindowSize(viewport.z, viewport.w); 
    glutCreateWindow("Dojo Raytracing");
    
    // GLEW
    glewInit();
    
    // App
    init();
    glutDisplayFunc(display);
//    glutReshapeFunc(onReshape);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    glutIdleFunc(onIdle);
    glutMainLoop();
    return 0;
}
