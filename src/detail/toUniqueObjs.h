#pragma once

namespace detail
{    
    
struct UniqueIDs
{
    std::size_t spheresId{0};
    std::size_t planesId{0};
    std::size_t lightsId{0};
    std::size_t materialsId{0};
};

struct MakeUniqueObj
{
    using result_type = Object;
    
    inline result_type operator()(const Sphere& model)
    { return {uniqueIds.spheresId++, model}; }
    
    inline result_type operator()(const Plane& model)
    { return {uniqueIds.planesId++, model}; }
    
    inline result_type operator()(const Light& model)
    { return {uniqueIds.lightsId++, model}; }
    
    inline result_type operator()(const Material& model)
    { return {uniqueIds.materialsId++, model}; }
    
    inline result_type operator()(const Camera& model)
    { return {0, model}; }
    
    UniqueIDs& uniqueIds;
};

template<typename Rng>
inline std::vector<Object> toUniqueObjs(Rng&& objects, UniqueIDs& uniqueIds)
{
    using value_t = typename ranges::range_value_t<Rng>;

    return objects 
        | ranges::view::transform(
            [&uniqueIds](const value_t& obj) mutable
            {
                MakeUniqueObj make{uniqueIds};
                return boost::apply_visitor(make, obj);
            })
        | ranges::to_vector;
}

}