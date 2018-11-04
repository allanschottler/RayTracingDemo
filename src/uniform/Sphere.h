#pragma once
#include "../model/Sphere.h"
#include "id2loc.h"

namespace uniform
{        
    template<typename Program>
    inline void load(const Program& program, const Sphere& model, std::string loc)
    {
        gl::uniform(program, model.center, loc + "center");
        gl::uniform(program, model.radius, loc + "radius");
    }
}