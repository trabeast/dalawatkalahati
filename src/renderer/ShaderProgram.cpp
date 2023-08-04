//
// Created by travisdev on 8/4/23.
//

#include "ShaderProgram.h"

namespace DTK {
    shader_program_t ShaderProgram::create() {
        return glCreateProgram();
    }
    void ShaderProgram::attachShader(shader_program_t program,
                                     shader_t shader) {
        glAttachShader(program, shader);
    }
    void ShaderProgram::link(shader_program_t program) {
        glLinkProgram(program);

        check<shader_program_t>(program, DTK_LINK_STATUS, glGetProgramiv,
                                glGetProgramInfoLog);
    }
    void ShaderProgram::use(shader_program_t program) {
        glUseProgram(program);
    }
}// namespace DTK