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

    Scene(Objects objects)
        : _objects(objects)
    {
        init();
    }

    Scene& operator=(const Scene& rhs)
    {
        _canvas = rhs._canvas;
        init();
        return *this;
    }

    Scene(Scene&&) = default;
    Scene& operator=(Scene&&) = default;

    const freijo::VAO& vao() const noexcept
    { return _vao; }
    
    const VBO& vertexes() const noexcept
    { return _canvas; }

    const freijo::program& program() const noexcept
    { return _program; }
    
    const Objects& objects() const noexcept
    { return _objects; }
    
private:
            
    /** Vertex Array Object(VAO) */
    freijo::VAO _vao;

    /** Vertex Buffer Object(VBO) */
    VBO _canvas {
        {0, 0},
        {1, 0},
        {1, 1},
        {0, 1}
    };

    void attachVBO()
    { _vao.attach(0, _canvas); }

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
      