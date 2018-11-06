#pragma once
#include "../model/Object.h"
#include "../util/readFile.h"
#include "toUniqueObjs.h"

#include <boost/lexical_cast.hpp>
#include <fstream>

using namespace ranges;

namespace detail
{    
    template<typename Parms>
    Sphere make(Parms&& p, spheres_tag)
    {
        assert(size(p) == 4);
        auto first = begin(p);
        glm::vec3 center{*next(first)};
        
    }
    
    object_t line2obj(const std::string& line)
    {
        auto tokens = line 
            | view::transform(std::tolower)
            | view::split(std::isspace);        
        
        auto parms = tokens 
            | view::drop(1)
            | view::transform(boost::lexical_cast<float>);
        
        switch(front(tokens))
        {
            case "sphere": return Sphere(std::move(parms), spheres_tag{});
        }
    }
    
    bool isComment(std::string line)
    { return *(line.begin()) == '#'; }
    
    std::vector<Object> loadScene(const std::string& sceneName)
    {
        std::string filePath = util::getRootDir() + "/data/" + sceneName;
        auto objs = util::readFile(filePath) 
            | view::split('\n');
            | view::filter(isComment)
            | view::transform(line2obj)
            | to_vector;
            
        return toUniqueObjs(std::move(objs));
    }
}