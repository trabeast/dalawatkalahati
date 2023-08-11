//
// Created by travisdev on 8/4/23.
//

#pragma once

#include "LogChecker.h"
#include "Shader.h"

namespace DTK {

    using shader_program_unit = unsigned int;

    class ShaderProgram : protected LogChecker {
    public:
        explicit ShaderProgram();
        virtual ~ShaderProgram();

        void attachShader(shader_unit shader) const;
        void link() const;
        void use() const;

    private:
        const shader_program_unit program;
        static shader_program_unit create();
    };

}// namespace DTK
