#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "tags.h"
            
/**
 * Modelo de luz de cena
 */            
class Material
{
public:    
    using tag_t = materials_tag;
    
    Material() = default;

    Material(float pdiffuseK,
             glm::vec4 pdiffuseColor,
             float pspecularK,
             float pshininess)
        : diffuseK(pdiffuseK)
        , diffuseColor(pdiffuseColor)
        , specularK(pspecularK)
        , shininess(pshininess)
    {}

    Material(const Material& rhs)
        : diffuseK(rhs.diffuseK)
        , diffuseColor(rhs.diffuseColor)
        , specularK(rhs.specularK)
        , shininess(rhs.shininess)
    {}

    Material& operator=(const Material& rhs)
    {
        diffuseK = rhs.diffuseK;
        diffuseColor = rhs.diffuseColor;
        specularK = rhs.specularK;
        shininess = rhs.shininess;
        return *this;
    }

    Material(Material&&) = default;
    Material& operator=(Material&&) = default;

    // Coeficiente de difusao
    float diffuseK;
    
    // Cor difusa
    glm::vec4 diffuseColor;
    
    // Coeficiente especular
    float specularK;
    
    // Coeficiente de brilho
    float shininess;
};
       
