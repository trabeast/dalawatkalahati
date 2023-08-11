//
// Created by travisdev on 8/4/23.
//

#include "ShaderProgram.h"

namespace DTK {

    ShaderProgram::ShaderProgram() : program(create()) {}

    ShaderProgram::~ShaderProgram() {
        GL_CHECK(glDeleteProgram(program));
    }

    void ShaderProgram::attachShader(shader_unit shader) const {
        GL_CHECK(glAttachShader(program, shader));
    }

    void ShaderProgram::link() const {
        GL_CHECK(glLinkProgram(program));

        check<shader_program_unit>(program, DTK_LINK_STATUS, glGetProgramiv,
                                   glGetProgramInfoLog);
    }
    void ShaderProgram::use() const {
        GL_CHECK(glUseProgram(program));
    }

    shader_program_unit ShaderProgram::create() {
        shader_program_unit program;
        GL_CHECK(program = glCreateProgram());
        return program;
    }
}// namespace DTK
