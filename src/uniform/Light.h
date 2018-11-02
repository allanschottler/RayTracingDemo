#pragma once
#include "../model/Light.h"
#include "id2loc.h"

namespace uniform
{        
    template<typename Program>
    inline void load(const Program& program, const Light& model, std::size_t id)
    {
        std::string loc = id2loc(id, lights_tag{});
        gl::uniform(program, model.position, loc + "position");
        gl::uniform(program, model.color, loc + "color");
    }
}