#pragma once
#include "../model/Object.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include "Material.h"

namespace uniform
{
    template<typename Program>
    struct LoadVisitor
    {
        using result_type = void;
        
        template<typename Model>
        result_type operator()(const Model& model) const
        { load(program, model, id2loc(id, typename Model::tag_t{})); }
        
        const Program& program;
        const std::size_t id;
    };
    
    template<typename Program>
    inline void load(const Program& program, const Object& obj)
    { boost::apply_visitor(LoadVisitor<Program>{program, obj.id}, obj.model); }
}