#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace gl
{
    template<typename Program, typename T>
    inline void uniform(const Program& program, const T& param, std::string loc);
    
    template<typename Program>
    inline void uniform(const Program& program, float param, std::string loc)
    {
        glUniform1f(glGetUniformLocation(program.id(), loc.c_str()), param);
    }    
        
    template<typename Program>
    inline void uniform(const Program& program, const glm::vec2& param, std::string loc)
    {
        glUniform2fv(glGetUniformLocation(program.id(), loc.c_str()), 1, glm::value_ptr(param));
    }
    
    template<typename Program>
    inline void uniform(const Program& program, const glm::vec3& param, std::string loc)
    {
        glUniform3fv(glGetUniformLocation(program.id(), loc.c_str()), 1, glm::value_ptr(param));
    }
    
    template<typename Program>
    inline void uniform(const Program& program, const glm::vec4& param, std::string loc)
    {
        glUniform4fv(glGetUniformLocation(program.id(), loc.c_str()), 1, glm::value_ptr(param));
    }
        
    template<typename Program>
    inline void uniform(const Program& program, const glm::mat4& param, std::string loc)
    {
        glUniformMatrix4fv(glGetUniformLocation(program.id(), loc.c_str()),
                           1, GL_FALSE, glm::value_ptr(param));
    }
}

