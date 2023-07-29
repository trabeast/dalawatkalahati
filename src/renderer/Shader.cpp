//
// Created by travisdev on 7/29/23.
//

#include "Shader.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

namespace DTK {
    unsigned int Shader::create(Type type, std::string &filePath) {
        std::string source = readContents(filePath);
        return 0;
    }

    std::string Shader::readContents(std::string &filePath) {
        std::ifstream file(filePath, std::ios_base::in);
        if(!file.is_open())
            throw std::runtime_error("Failed to open " + filePath);
        using Iterator = std::istreambuf_iterator<char>;
        std::string content(Iterator{file}, Iterator{});
        if(!file)
            throw std::runtime_error("Failed to open " + filePath);
        return content;
    }
} // DTK