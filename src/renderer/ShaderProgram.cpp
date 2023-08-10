//
// Created by travisdev on 8/4/23.
//

#include "ShaderProgram.h"

namespace DTK {
    shader_program_t ShaderProgram::create() {
        shader_program_t program;
        GL_CHECK(program = glCreateProgram());
        return program;
    }
    void ShaderProgram::attachShader(shader_program_t program,
                                     shader_unit shader) {
        GL_CHECK(glAttachShader(program, shader));
    }
    void ShaderProgram::link(shader_program_t program) {
        GL_CHECK(glLinkProgram(program));

        check<shader_program_t>(program, DTK_LINK_STATUS, glGetProgramiv,
                                glGetProgramInfoLog);
    }
    void ShaderProgram::use(shader_program_t program) {
        GL_CHECK(glUseProgram(program));
    }
}// namespace DTK
