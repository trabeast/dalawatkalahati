//
// Created by travisdev on 7/29/23.
//

#pragma once

#include "common.h"
#include <string>

namespace DTK {

    enum Type {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
    };

    class Shader {
    public:
        unsigned int create(Type type, std::string &filePath);
    private:
        std::string readContents(std::string &filePath);
    };

} // DTK
