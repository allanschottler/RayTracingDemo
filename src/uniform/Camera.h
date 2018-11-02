#pragma once
#include "../model/Camera.h"
#include "id2loc.h"

#include <glm/gtc/matrix_transform.hpp>

namespace uniform
{        
    template<typename Program>
    inline void load(const Program& program, const Camera& model, std::size_t id)
    {
        glm::mat4 view = model.modelview;
        glm::mat4 projection = model.projection;
        glm::vec4 viewport = model.viewport;
        
        gl::uniform(program, view, "view");
        gl::uniform(program, projection, "projection");
        gl::uniform(program, glm::vec2{viewport.z, viewport.w}, "viewport");
        
        int width  = viewport.z;
        int height = viewport.w;
        
        // Pega pontos do near e far
        glm::vec3 nearCenter     {width/2.f, height/2.f, 0.f};
        glm::vec3 nearHorizontal {width, height/2.f, 0.f};
        glm::vec3 nearVertical   {width/2.f, height, 0.f};            
        glm::vec3 farCenter      {width/2.f, height/2.f, 1.f};
        glm::vec3 farHorizontal  {width, height/2.f, 1.f};
        glm::vec3 farVertical    {width/2.f, height, 1.f};
        
        // Transforma pontos para mundo
        nearCenter     = glm::unProject(nearCenter, view, projection, viewport);
        nearHorizontal = glm::unProject(nearHorizontal, view, projection, viewport);
        nearVertical   = glm::unProject(nearVertical, view, projection, viewport);
        farCenter      = glm::unProject(farCenter, view, projection, viewport);
        farHorizontal  = glm::unProject(farHorizontal, view, projection, viewport);
        farVertical    = glm::unProject(farVertical, view, projection, viewport);
        
        // Passa pontos para o programa
        gl::uniform(program, nearCenter, "nearCenter");
        gl::uniform(program, nearHorizontal - nearCenter, "nearRight");
        gl::uniform(program, nearVertical - nearCenter, "nearUp");
        gl::uniform(program, farCenter, "farCenter");
        gl::uniform(program, farHorizontal - farCenter, "farRight");
        gl::uniform(program, farVertical - farCenter, "farUp");
    }
}