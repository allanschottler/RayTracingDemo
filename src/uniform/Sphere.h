#pragma once
#include "../model/Sphere.h"

namespace uniform
{
    inline std::string index2loc(int index)
    {
        std::string base = "spheres";
        return index < 0 ? base : base + "[" + std::to_string(index) + "]."; 
    }
        
    template<typename Program>
    inline void load(const Program& program, const Sphere& model, int index = -1)
    {
        std::string loc = index2loc(index);
        gl::uniform(program, model.center, loc + "center");
        gl::uniform(program, model.radius, loc + "radius");
        gl::uniform(program, model.color,  loc + "color");
    }
}