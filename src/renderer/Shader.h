//
// Created by travisdev on 7/29/23.
//

#pragma once

#include "LogChecker.h"
#include <string>

namespace DTK {

    using shader_t = unsigned int;


    class Shader : protected LogChecker {
    public:
        enum class Type {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
        };

        static shader_t create(Type type);
        static bool compile(shader_t shader, const std::string &filePath);
        static void destroy(shader_t shader);

    private:
        static void readContents(const std::string &filePath,
                                 std::string &source);
    };

}// namespace DTK
