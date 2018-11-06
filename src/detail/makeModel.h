#pragma once
#include "../model/Object.h"
#include <cassert>

namespace detail
{    
    template<typename Parms, typename Tag>
    object_t make(Parms&& p, Tag);
    
    template<typename Parms>
    object_t make(Parms&& p, cameras_tag)
    {
        assert(size(p) == 18);
        return Camera(
            glm::lookAt(
                {at(p, 0), at(p, 1), at(p, 2)},     // EYE
                {at(p, 0), at(p, 1), at(p, 2)},     // CENTER
                {at(p, 0), at(p, 1), at(p, 2)}),    // UP
            glm::perspective(
                glm::radians(at(p, 0)),             // FOVY
                at(p, 0) / at(p, 0),                // ASPECT
                at(p, 0),                           // NEAR
                at(p, 0)),                          // FAR
            glm::vec4{
                at(p, 0),                           // VP.X          
                at(p, 1),                           // VP.Y
                at(p, 2),                           // VP.W
                at(p, 3)});                         // VP.H
    }
    
    template<typename Parms>
    object_t make(Parms&& p, materials_tag)
    {
        assert(size(p) == 8);
        return Material(
            at(p, 1),                                   // DIFF K
            {at(p, 2), at(p, 3), at(p, 4), at(p, 5)},   // DIFF COLOR
            at(p, 6),                                   // SPEC K
            at(p, 7));                                  // SHININESS
    }
    
    template<typename Parms>
    object_t make(Parms&& p, lights_tag)
    {
        assert(size(p) == 6);
        return Light(
            {at(p, 0), at(p, 1), at(p, 2)},   // POSITION
            {at(p, 3), at(p, 4), at(p, 5)});  // COLOR
    }
    
    template<typename Parms>
    object_t make(Parms&& p, spheres_tag)
    {
        assert(size(p) == 4);
        return Sphere(
            {at(p, 0), at(p, 1), at(p, 2)}, 
            at(p, 3));        
    }
    
    template<typename Parms>
    object_t make(Parms&& p, planes_tag)
    {
        assert(size(p) == 6);
        return Plane(
            {at(p, 0), at(p, 1), at(p, 2)}, 
            {at(p, 3), at(p, 4), at(p, 5)});        
    }
}