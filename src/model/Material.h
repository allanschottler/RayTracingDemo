#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
            
/**
 * Modelo de luz de cena
 */            
class Material
{
public:    
    
    Material() = default;

    Material(float pdiffuseK,
             glm::vec4 pdiffuseColor,
             float pspecularK,
             float shininess)
        : diffuseK(pdiffuseK)
        , diffuseColor(pdiffuseColor)
        , specularK(pspecularK)
    {}

    Material(const Material& rhs)
        : diffuseK(rhs.diffuseK)
        , diffuseColor(rhs.diffuseColor)
        , specularK(rhs.specularK)
    {}

    Material& operator=(const Material& rhs)
    {
        diffuseK = rhs.diffuseK;
        diffuseColor = rhs.diffuseColor;
        specularK = rhs.specularK;
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
    
    // Coeficiente especular
    float shininessK;
};
       
