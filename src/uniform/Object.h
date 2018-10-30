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
        { load(program, model, index); }
        
        const Program& program;
        const int index;
    };
    
    template<typename Program>
    inline void load(const Program& program, const Object& model, int index = -1)
    { boost::apply_visitor(LoadVisitor<Program>{program, index}, model); }
}