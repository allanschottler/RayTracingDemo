#pragma once
#include "Object.h"
#include "Camera.h"
#include "../util/readFile.h"
#include "../util/getWorkingDir.h"

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
    
    //Scene() = default;

    Scene(Camera& camera, Objects pobjects, glm::vec3 plightPos)
        : lightPos(plightPos)
        , _camera(camera)
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
    
    glm::mat4 transform;
        
    const freijo::VAO& vao() const noexcept
    { return _vao; }
    
    const VBO& vertexes() const noexcept
    { return _quad; }

    const freijo::program& program() const noexcept
    { return _program; }
    
    const Camera& camera() const noexcept
    { return _camera; }
    
    const Objects& objects() const noexcept
    { return _objects; }
    
private:
            
    /** Vertex Array Object(VAO) */
    freijo::VAO _vao;

    /** Vertex Buffer Object(VBO) */
    VBO _quad {
        {-1, -1},
        {1, -1},
        {1, 1},
        {-1, 1}
    };

    void attachVBO()
    { _vao.attach(0, _quad); }

    //** Programa OpenGL com os devidos shaders */
    freijo::program _program; 
    
    Camera& _camera;
    
    Objects _objects;
    
    void init()
    {
        attachVBO();

        try
        {
            std::string shadersPath = util::getRootDir() + "/src/shader/";
            auto vs = util::readFile(shadersPath + "Scene.vs");
            auto fs = util::readFile(shadersPath + "Scene.fs");
                        
            _program = freijo::program{
                freijo::vertex_shader(vs).id(),
                freijo::fragment_shader(fs).id()
            };
        }
        catch(const std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }         
};
      