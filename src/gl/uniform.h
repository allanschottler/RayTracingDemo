#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace gl
{
    template<typename Program, typename T>
    void uniform(const Program& program, const T& param, std::string loc);
    
    template<typename Program>
    void uniform(const Program& program, const glm::vec2 param, std::string loc)
    {
        glUniform2fv(glGetUniformLocation(program.id(), loc.c_str()), 1, glm::value_ptr(param));
    }
    
    template<typename Program>
    void uniform(const Program& program, const glm::vec3 param, std::string loc)
    {
        glUniform3fv(glGetUniformLocation(program.id(), loc.c_str()), 1, glm::value_ptr(param));
    }
    
    template<typename Program>
    void uniform(const Program& program, const glm::mat4 param, std::string loc)
    {
        glUniformMatrix4fv(glGetUniformLocation(program.id(), loc.c_str()),
                           1, GL_FALSE, glm::value_ptr(param));
    }
}

