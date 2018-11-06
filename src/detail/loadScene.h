#pragma once
#include "../model/Object.h"
#include "../util/readFile.h"
#include "toUniqueObjs.h"
#include "makeModel.h"

#include <boost/lexical_cast.hpp>
#include <fstream>

using namespace ranges;

namespace detail
{    
    object_t line2obj(const std::string& line)
    {           
        auto tokens = view::split(line, (int(*)(int))&std::isspace);        
        
        auto parms = tokens 
            | view::drop(1)
            | view::transform(boost::lexical_cast<float, std::string>);
        
        std::string id = front(tokens);
        
        if(id == "Camera")        return make(std::move(parms), cameras_tag{});
        else if(id == "Light")    return make(std::move(parms), lights_tag{});
        else if(id == "Material") return make(std::move(parms), materials_tag{});
        else if(id == "Plane")    return make(std::move(parms), planes_tag{});
        else if(id == "Sphere")   return make(std::move(parms), spheres_tag{});
        else throw std::runtime_error("Unknown: " + id);
    }
    
    bool isComment(std::string line)
    { return line.front() == '#'; }
    
    std::vector<object_t> loadScene(const std::string& sceneName)
    {
        std::string filePath = util::getRootDir() + "/data/" + sceneName;
        auto str = util::readFile(filePath);
        return view::split(str, '\n')
            | view::filter(isComment)
            | view::transform(line2obj)
            | to_vector;
    }
}