#pragma once
#include "../model/Object.h"
#include "../uniform/Sphere.h"

namespace uniform
{
    struct LoadVisitor
    {
        using result_type = void;
        
        template<typename Model>
        result_type operator()(const Model& model) const
        {
            load(model);
        }
    };
    
    void load(const Object& model)
    {
        boost::apply_visitor(LoadVisitor{}, model);
    }
}