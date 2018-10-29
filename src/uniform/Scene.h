#pragma once
#include "../gl/uniform.h"
#include "../model/Scene.h"
#include "Object.h"

#include <glm/gtc/matrix_transform.hpp>

namespace uniform
{
    template<typename Program>
    void load(const Program& program, const Scene& model)
    {
        /******************************************************************************************/
        /*      Uniformes da câmera                                                               */
        /******************************************************************************************/
        glm::vec4 viewport;
        glGetFloatv(GL_VIEWPORT, glm::value_ptr(viewport)); 

        int width = viewport.z;
        int height = viewport.w;

        glm::mat4 modelview, projection;
        glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(modelview));
        glGetFloatv(GL_PROJECTION_MATRIX, glm::value_ptr(modelview));

        gl::uniform(program, modelview, "modelview");
        gl::uniform(program, projection, "projection");
        gl::uniform(program, glm::vec2{width, height}, "viewport");  
        gl::uniform(program, model.lightPos, "lightPos");
        
        /******************************************************************************************/
        /*      Uniformes de frustrum                                                             */
        /******************************************************************************************/
//        glm::dmat4 modelview , projection;
//        glGetDoublev(GL_MODELVIEW_MATRIX,  glm::value_ptr(modelview));
//        glGetDoublev(GL_PROJECTION_MATRIX, glm::value_ptr(projection));

        // pega centro do near
        glm::vec3 nearCenter     {width/2.f, height/2.f, 0.f};
        glm::vec3 nearHorizontal {width, height/2.f, 0.f};
        glm::vec3 nearVertical   {width/2.f, height, 0.f};            
        glm::vec3 farCenter      {width/2.f, height/2.f, 1.f};
        glm::vec3 farHorizontal  {width, height/2.f, 1.f};
        glm::vec3 farVertical    {width/2.f, height, 1.f};
        
        nearCenter = glm::unProject(nearCenter, modelview, projection, viewport);
        nearHorizontal = glm::unProject(nearHorizontal, modelview, projection, viewport);
        nearVertical = glm::unProject(nearVertical, modelview, projection, viewport);
        farCenter = glm::unProject(farCenter, modelview, projection, viewport);
        farHorizontal = glm::unProject(farHorizontal, modelview, projection, viewport);
        farVertical = glm::unProject(farVertical, modelview, projection, viewport);
        
        gl::uniform(program, nearCenter, "nearCenter");
        gl::uniform(program, nearHorizontal - nearCenter, "nearRight");
        gl::uniform(program, nearVertical - nearCenter, "nearUp");
        gl::uniform(program, farCenter, "farCenter");
        gl::uniform(program, farHorizontal - farCenter, "farRight");
        gl::uniform(program, farVertical - farCenter, "farUp");        
    }
}

