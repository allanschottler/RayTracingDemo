#pragma once
#include "../model/Scene.h"
#include "../uniform/Scene.h"

#include <GL/glew.h>
#include <GL/glx.h>
#include <glm/gtx/io.hpp>

#include "../gl/disable.h"
#include "../gl/matrixMode.h"
#include "../gl/DebugMessage.h"

inline void render(const Scene& scene)
{   
    // Print de erros GL
    gl::DebugMessage dbm();
    
    // Bind VAO
    freijo::scoped_vao_bind svb(scene.vao());
    
    // Load program
    scene.program().use();
    
    // Define cor branca default
    glColor4f(1, 1, 1, 1);
    
    // Desabilita teste de profundidade
    gl::Disable(GL_DEPTH_TEST);

    // Define projeção ortográfica
    gl::MatrixMode(GL_PROJECTION);    
    glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);

    gl::MatrixMode(GL_MODELVIEW);        
    
    // Passa uniformes para shader
    uniform::load(scene.program(), scene);
    
    // Desenha um quad.
    const auto& vertexes = scene.vertexes();
    glDrawArrays(GL_QUADS, 0, vertexes.size());  
    
    // Unload program
    glUseProgram(0);
}