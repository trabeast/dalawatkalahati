//
// Created by travisdev on 7/29/23.
//

#include "Shader.h"
#include <fstream>
#include <iterator>

namespace DTK {
    Shader::Shader(Type type) : shader(create(type)) {}

    bool Shader::compile(const std::string &filePath) const {
        std::string source;
        const char *sourcePtr;
        readContents(filePath, source);
        sourcePtr = source.c_str();

        GL_CHECK(glShaderSource(shader, 1, &sourcePtr, nullptr));
        GL_CHECK(glCompileShader(shader));

        return check<shader_unit>(shader, DTK_COMPILE_STATUS, glGetShaderiv,
                                  glGetShaderInfoLog);
    }

    Shader::~Shader() {
        GL_CHECK(glDeleteShader(shader));
    }


    void Shader::readContents(const std::string &filePath,
                              std::string &source) {
        try {
            std::ifstream file(filePath, std::ios_base::in);
            if (!file.is_open()) {
                DTK_LOGGER_ERROR("Failed to open!");
                abort();
            }
            using Iterator = std::istreambuf_iterator<char>;
            source = std::string(Iterator{file}, Iterator{});
        } catch (const std::ios_base::failure &e) {
            DTK_LOGGER_ERROR("Caused by {}", e.what());
        }
    }
    shader_unit Shader::create(Shader::Type type) {
        shader_unit sh;
        GL_CHECK(sh = glCreateShader(static_cast<GLenum>(type)));
        return sh;
    }
}// namespace DTK
