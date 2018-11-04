#pragma once
#include <glm/vec3.hpp>
#include "tags.h"

/**
 * Modelo de desenho de uma esfera
 */            
class Plane
{
public:    
    using tag_t = planes_tag;
    
    Plane() = default;

    Plane(glm::vec3 ppoint, 
          glm::vec3 pnormal)
        : point(ppoint)
        , normal(pnormal)
    {}

    Plane(const Plane& rhs)
        : point(rhs.point)
        , normal(rhs.normal)
    {}

    Plane& operator=(const Plane& rhs)
    {
        point = rhs.point;
        normal = rhs.normal;
        return *this;
    }

    Plane(Plane&&) = default;
    Plane& operator=(Plane&&) = default;

    /** Ponto no plano */
    glm::vec3 point;
    
    /** Normal do plano */
    glm::vec3 normal;
};
       
