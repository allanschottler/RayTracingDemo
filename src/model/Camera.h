#pragma once
#include <glm/mat4x4.hpp>
#include <utility>

struct Camera
{
    Camera() = default;

    Camera(glm::mat4 pmodelview, glm::mat4 pprojection, glm::vec4 pviewport)
        : modelview(std::move(pmodelview))
        , projection(std::move(pprojection))
        , viewport(std::move(pviewport))
    {}

    Camera(const Camera& rhs)
        : modelview(rhs.modelview)
        , projection(rhs.projection)
        , viewport(rhs.viewport)
    {}
    
    Camera& operator=(const Camera& rhs)
    {
        modelview = rhs.modelview;
        projection = rhs.projection;
        viewport = rhs.viewport;
        return *this;
    }

    Camera(Camera&&) = default;
    Camera& operator=(Camera&&) = default;
    
    glm::mat4 modelview;
    glm::mat4 projection;
    glm::vec4 viewport;
};
