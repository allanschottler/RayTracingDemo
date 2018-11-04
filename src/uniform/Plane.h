#pragma once
#include "../model/Sphere.h"
#include "id2loc.h"

namespace uniform
{        
    template<typename Program>
    inline void load(const Program& program, const Plane& model, std::string loc)
    {
        gl::uniform(program, model.point, loc + "point");
        gl::uniform(program, model.normal, loc + "normal");
    }
}