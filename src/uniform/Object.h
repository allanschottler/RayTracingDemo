#pragma once
#include "../model/Object.h"
#include "../uniform/Sphere.h"

namespace uniform
{
    template<typename Program>
    struct LoadVisitor
    {
        using result_type = void;
        
        template<typename Model>
        result_type operator()(const Model& model) const
        { load(program, model); }
        
        const Program& program;
    };
    
    template<typename Program>
    void load(const Program& program, const Object& model)
    { boost::apply_visitor(LoadVisitor<Program>{program}, model); }
}