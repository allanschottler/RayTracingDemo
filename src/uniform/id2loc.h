#pragma once
#include "tags.h"

namespace uniform
{
    template<typename Tag>
    inline std::string id2loc(int id, Tag tag);
    
    template<>
    inline std::string id2loc(int id, spheres_tag tag)
    {
        std::string base = "spheres";
        return id < 0 ? base : base + "[" + std::to_string(id) + "]."; 
    }
    
    template<>
    inline std::string id2loc(int id, lights_tag tag)
    {
        return "light.";
    }
    
    template<>
    inline std::string id2loc(int id, materials_tag tag)
    {
        return "material.";
    }
}