//
// Created by travisdev on 8/4/23.
//

#pragma once

#include "LogChecker.h"
#include "Shader.h"

namespace DTK {

    using shader_program_t = unsigned int;

    class ShaderProgram : protected LogChecker {
    public:
        static shader_program_t create();
        static void attachShader(shader_program_t program, shader_t shader);
        static void link(shader_program_t program);
        static void use(shader_program_t program);
    };

}// namespace DTK
