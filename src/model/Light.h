#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "tags.h"

/**
 * Modelo de luz de cena
 */            
class Light
{
public:    
    using tag_t = lights_tag;
    
    Light() = default;

    Light(glm::vec3 pposition,
          glm::vec4 pcolor = {1, 1, 1, 1})
        : position(pposition)
        , color(pcolor)
    {}

    Light(const Light& rhs)
        : position(rhs.position)
        , color(rhs.color)
    {}

    Light& operator=(const Light& rhs)
    {
        position = rhs.position;
        color = rhs.color;
        return *this;
    }

    Light(Light&&) = default;
    Light& operator=(Light&&) = default;

    /** Posicao da luz */
    glm::vec3 position;
        
    /** Cor RGBA da luz */
    glm::vec4 color;        
};
       
