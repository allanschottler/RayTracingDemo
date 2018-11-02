#pragma once

namespace detail
{    
    
struct MakeUniqueObj
{
    using result_type = Object;
    
    inline result_type operator()(const Sphere& model)
    { return {spheresId++, model}; }
    
    inline result_type operator()(const Light& model)
    { return {lightsId++, model}; }
    
    inline result_type operator()(const Material& model)
    { return {materialsId++, model}; }
    
    inline result_type operator()(const Camera& model)
    { return {0, model}; }
    
    std::size_t& spheresId;
    std::size_t& lightsId;
    std::size_t& materialsId;
};

template<typename Rng>
inline std::vector<Object> toUniqueObjs(Rng&& objects)
{
    using value_t = typename ranges::range_value_t<Rng>;
    std::size_t spheresId{0};
    std::size_t lightsId{0};
    std::size_t materialsId{0};

    return objects 
        | ranges::view::transform(
            [&spheresId, &lightsId, &materialsId]
            (const value_t& obj) mutable
            {
                MakeUniqueObj make{spheresId, lightsId, materialsId};
                return boost::apply_visitor(make, obj);
            })
        | ranges::to_vector;
}

}