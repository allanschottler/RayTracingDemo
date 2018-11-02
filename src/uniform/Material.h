#pragma once
#include "../model/Material.h"
#include "id2loc.h"

namespace uniform
{        
    template<typename Program>
    inline void load(const Program& program, const Material& model, std::size_t id)
    {
        std::string loc = id2loc(id, materials_tag{});
        gl::uniform(program, model.diffuseK, loc + "diffuseK");
        gl::uniform(program, model.diffuseColor, loc + "diffuseColor");
        gl::uniform(program, model.specularK,  loc + "specularK");
    }
}


