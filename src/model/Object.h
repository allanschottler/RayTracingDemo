#pragma once
#include "Sphere.h"
#include "Light.h"
#include "Material.h"
#include <boost/variant.hpp>

using object_t = boost::variant<
    Sphere,
    Light,
    Material
>;

struct Object
{
    Object(std::size_t pid, object_t pmodel)
        : id(pid)
        , model(std::move(pmodel))
    {}

    Object(Object&&) = default;
    Object& operator=(Object&&) = default;
    
    std::size_t id{0};
    object_t model;
};