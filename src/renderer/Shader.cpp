//
// Created by travisdev on 7/29/23.
//

#include "Shader.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

namespace DTK {
    shader_t Shader::create(Type type) {

        shader_t shader = glCreateShader(static_cast<GLenum>(type));

        return shader;
    }

    bool Shader::compile(shader_t shader, const std::string &filePath) {
        std::string source;
        const char *sourcePtr;
        readContents(filePath, source);
        sourcePtr = source.c_str();

        glShaderSource(shader, 1, &sourcePtr, nullptr);
        glCompileShader(shader);

        return check<shader_t>(shader, DTK_COMPILE_STATUS, glGetShaderiv,
                               glGetShaderInfoLog);
    }

    void Shader::destroy(shader_t shader) {
        glDeleteShader(shader);
    }

    void Shader::readContents(const std::string &filePath,
                              std::string &source) {
        try {
            std::ifstream file(filePath, std::ios_base::in);
            if (!file.is_open()) {
                DTK_LOGGER_ERROR("Failed to open!");
                throw std::ios_base::failure("Failed to open " + filePath);
            }
            using Iterator = std::istreambuf_iterator<char>;
            source = std::string(Iterator{file}, Iterator{});
        } catch (const std::ios_base::failure &e) {
            DTK_LOGGER_ERROR("Caused by {}", e.what());
        }
    }
}// namespace DTK