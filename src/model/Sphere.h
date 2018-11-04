#pragma once
#include <glm/vec3.hpp>
#include "tags.h"
            
/**
 * Modelo de desenho de uma esfera
 */            
class Sphere
{
public:    
    using tag_t = spheres_tag;
    
    Sphere() = default;

    Sphere(glm::vec3 pcenter,
           float pradius = 1)
        : center(pcenter)
        , radius(pradius)
    {}

    Sphere(const Sphere& rhs)
        : center(rhs.center)
        , radius(rhs.radius)
    {}

    Sphere& operator=(const Sphere& rhs)
    {
        center = rhs.center;
        radius = rhs.radius;
        return *this;
    }

    Sphere(Sphere&&) = default;
    Sphere& operator=(Sphere&&) = default;

    /** Centro da esfera */
    glm::vec3 center;
    
    /** Raio da esfera*/
    float radius;      
};
       
