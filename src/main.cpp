#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#include "model/Scene.h"
#include "render/Scene.h"
#include "model/Object.h"

#include <iostream>

/***************************************/
/*  GLOBALS                            */
/***************************************/
std::vector<Object> g_objs
    { Sphere({1, 1, 0}) };
    
Scene* g_scene = nullptr;

glm::vec3 g_lightPos{1, 1, 1};

int last_mx = 0, last_my = 0, cur_mx = 0, cur_my = 0;
int arcball_on = false;

glm::vec4 viewport{0, 0, 800, 600};
         
Camera cam {
    glm::lookAt(glm::vec3{0, 0, 2}, glm::vec3{0, 0, 0}, glm::vec3{0, 1, 0}),
    glm::perspective(40.f, viewport.z/viewport.w, 0.01f, 10.f),
    viewport
};
    
/***************************************/
/*  GL INIT                            */
/***************************************/

/**
 * Get a normalized vector from the center of the virtual ball O to a
 * point P on the virtual ball surface, such that P is aligned on
 * screen's (X,Y) coordinates.  If (X,Y) is too far away from the
 * sphere, return the nearest point on the virtual ball surface.
 */
glm::vec3 get_arcball_vector(int x, int y) 
{
    glm::vec3 P = glm::vec3(1.0 * x/viewport.z * 2 - 1.0,
                            1.0 * y/viewport.w * 2 - 1.0,
                            0);
    P.y = -P.y;
    float OP_squared = P.x * P.x + P.y * P.y;
    if(OP_squared <= 1*1)
        P.z = sqrt(1*1 - OP_squared);  // Pythagoras
    else
        P = glm::normalize(P);  // nearest point
    return P;
}

void onMouse(int button, int state, int x, int y) 
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        arcball_on = true;
        last_mx = cur_mx = x;
        last_my = cur_my = y;
    } 
    else 
    {
        arcball_on = false;
    }
}

void onMotion(int x, int y) 
{
    if(arcball_on) 
    {
        cur_mx = x;
        cur_my = y;
    }
}

void onIdle()
{
    if(cur_mx != last_mx || cur_my != last_my) 
    {
        glm::vec3 va = get_arcball_vector(last_mx, last_my);
        glm::vec3 vb = get_arcball_vector(cur_mx,  cur_my);
        float angle = acos(std::min(1.0f, glm::dot(va, vb)));
        glm::vec4 axis_in_camera_coord = glm::vec4(glm::cross(va, vb), 1);
        glm::mat4 camera2object = glm::inverse(cam.modelview) * g_scene->transform;
        glm::vec4 axis_in_object_coord = camera2object * axis_in_camera_coord;
        g_scene->transform = glm::rotate(
            g_scene->transform, 
            glm::degrees(angle), 
            glm::vec3{axis_in_object_coord});
        last_mx = cur_mx;
        last_my = cur_my;
        
        glutPostRedisplay();
    }        
}

void onReshape(int width, int height) 
{
    cam.viewport.z = width;
    cam.viewport.w = height;
    glViewport(cam.viewport.x, cam.viewport.y, width, height);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    render(*g_scene);
    glutSwapBuffers();
}

void init() 
{    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    if(g_scene) delete g_scene;    
    g_scene = new Scene(cam, g_objs, g_lightPos);
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
    glutReshapeFunc(onReshape);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    glutIdleFunc(onIdle);
    glutMainLoop();
    return 0;
}
