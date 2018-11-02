#pragma once
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glext.h>

#include <freijo/VAO.hpp>
#include <freijo/buffer.hpp>
#include <freijo/program.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
            
/**
 * Modelo de desenho de uma esfera
 */            
class Sphere
{
public:    
    
    Sphere() = default;

    Sphere(glm::vec3 pcenter,
           float pradius = 1,
           glm::vec4 pcolor = {1, 0, 0, 1})
        : center(pcenter)
        , radius(pradius)
        , color(pcolor)
    {}

    Sphere(const Sphere& rhs)
        : center(rhs.center)
        , radius(rhs.radius)
        , color(rhs.color)
    {}

    Sphere& operator=(const Sphere& rhs)
    {
        center = rhs.center;
        radius = rhs.radius;
        color = rhs.color;
        return *this;
    }

    Sphere(Sphere&&) = default;
    Sphere& operator=(Sphere&&) = default;

    /** Centro da esfera */
    glm::vec3 center;
    
    /** Raio da esfera*/
    float radius;
    
    /** Cor RGBA da esfera */
    glm::vec4 color;        
};
       
