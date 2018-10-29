#pragma once
#include "Object.h"

#include <freijo/VAO.hpp>
#include <freijo/buffer.hpp>
#include <freijo/program.hpp>
#include <freijo/shader.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <iostream>

/**
 * Modelo de desenho da cena
 */
class Scene
{
public:    
    using Objects = std::vector<Object>;
    using VBO = freijo::VBO<glm::vec2>;
    
    Scene() = default;

    Scene(Objects pobjects, glm::vec3 plightPos)
        : lightPos(plightPos)
        , _objects(pobjects)
    {
        init();
    }

    Scene& operator=(const Scene& rhs)
    {
        _quad = rhs._quad;
        init();
        return *this;
    }

    Scene(Scene&&) = default;
    Scene& operator=(Scene&&) = default;

    glm::vec3 lightPos;
    
    const freijo::VAO& vao() const noexcept
    { return _vao; }
    
    const VBO& vertexes() const noexcept
    { return _quad; }

    const freijo::program& program() const noexcept
    { return _program; }
    
    const Objects& objects() const noexcept
    { return _objects; }
    
private:
            
    /** Vertex Array Object(VAO) */
    freijo::VAO _vao;

    /** Vertex Buffer Object(VBO) */
    VBO _quad {
        {0, 0},
        {1, 0},
        {1, 1},
        {0, 1}
    };

    void attachVBO()
    { _vao.attach(0, _quad); }

    //** Programa OpenGL com os devidos shaders */
    freijo::program _program; 
    
    Objects _objects;
    
    void init()
    {
        attachVBO();

        try
        {
            _program = freijo::program{
                freijo::vertex_shader("").id(),
                freijo::fragment_shader("").id()
            };
        }
        catch(const std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }         
};
      