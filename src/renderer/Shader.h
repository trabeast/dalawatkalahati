//
// Created by travisdev on 7/29/23.
//

#pragma once

#include "LogChecker.h"
#include <string>

namespace DTK {

    using shader_unit = unsigned int;

    class Shader : protected LogChecker {
    public:
        enum class Type {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
        };

        explicit Shader(Type type);
        virtual ~Shader();

        const shader_unit shader;

        [[nodiscard]] bool compile(const std::string &filePath) const;

    private:
        static void readContents(const std::string &filePath,
                                 std::string &source);

        static shader_unit create(Type type);
    };

}// namespace DTK
