#pragma once
#include "../model/tags.h"

namespace uniform
{
    template<typename Tag>
    inline std::string id2loc(std::size_t id, Tag tag);
    
    template<>
    inline std::string id2loc(std::size_t id, spheres_tag tag)
    {
        std::string base = "spheres";
        return id < 0 ? base : base + "[" + std::to_string(id) + "]."; 
    }
    
    template<>
    inline std::string id2loc(std::size_t id, planes_tag tag)
    { return "ground."; }
    
    template<>
    inline std::string id2loc(std::size_t id, lights_tag tag)
    { return "light."; }
    
    template<>
    inline std::string id2loc(std::size_t id, materials_tag tag)
    { return "material."; }
    
    template<typename Tag>
    inline std::string id2loc(std::size_t id, Tag tag)
    { return ""; }
}