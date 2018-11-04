#pragma once
#include <glm/mat4x4.hpp>
#include <utility>

namespace detail
{
struct Arcball
{
    Arcball(glm::mat4 pmodelview, glm::mat4 pprojection, glm::vec4 pviewport)
        : modelview(pmodelview)
        , projection(pprojection)
        , viewport(pviewport)
    {}
    
    Arcball(const Arcball&) = delete;
    Arcball& operator=(const Arcball& rhs) = delete;
        
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
            radius = 0;
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
    
    bool onIdle(glm::mat4& transform)
    {
        if(cur_mx != last_mx || cur_my != last_my) 
        {
            glm::vec3 va = get_arcball_vector(last_mx, last_my);
            glm::vec3 vb = get_arcball_vector(cur_mx,  cur_my);
            float angle = acos(std::min(1.0f, glm::dot(va, vb)));
            glm::vec4 axis_in_camera_coord = glm::vec4(glm::cross(va, vb), 1);
//            glm::mat4 camera2object = glm::inverse(modelview) * transform;
//            glm::vec4 axis_in_object_coord = camera2object * axis_in_camera_coord;
            transform = glm::rotate(
                transform, 
                glm::degrees(angle), 
                glm::vec3{axis_in_camera_coord});
            last_mx = cur_mx;
            last_my = cur_my;
            return true;
        }        
        return false;
    }
    
private:
    /**
     * Get a normalized vector from the center of the virtual ball O to a
     * point P on the virtual ball surface, such that P is aligned on
     * screen's (X,Y) coordinates.  If (X,Y) is too far away from the
     * sphere, return the nearest point on the virtual ball surface.
     */
    glm::vec3 get_arcball_vector(int x, int y) 
    {
        glm::vec3 world = glm::unProject(glm::vec3{x, y, 0.f}, modelview, projection, viewport);
//        if(!radius)
//            radius = glm::length(world);
        return glm::normalize(world);// * radius;
    }
    
//    glm::vec3 get_arcball_vector(int x, int y) 
//    {
//        glm::vec3 P = glm::vec3(1.0 * x/viewport.z * 2 - 1.0,
//                                1.0 * y/viewport.w * 2 - 1.0,
//                                0);
//        P.y = -P.y;
//        float OP_squared = P.x * P.x + P.y * P.y;
//        if(OP_squared <= 1*1)
//            P.z = sqrt(1*1 - OP_squared);  // Pythagoras
//        else
//            P = glm::normalize(P);  // nearest point
//        return P;
//    }

    int last_mx{0}, last_my{0}, cur_mx{0}, cur_my{0};
    bool arcball_on{false};
    float radius{0};
    glm::mat4 modelview;
    glm::mat4 projection;
    glm::vec4 viewport;
};
}