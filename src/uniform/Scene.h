#pragma once
#include "../gl/uniform.h"
#include "../model/Scene.h"
#include "Object.h"

#include <range/v3/all.hpp>

namespace uniform
{
    template<typename Program>
    inline void load(const Program& program, const Scene& model)
    {      
        // Passa transformacao da cena
        gl::uniform(program, model.transform, "model");
        
        // Passa objetos para o programa
        ranges::for_each(model.objects(),
            [&program](const Object& obj)
            { uniform::load(program, obj); });
    }
}

