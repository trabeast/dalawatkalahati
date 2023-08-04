//
// Created by travisdev on 7/23/23.
//

#pragma once

#include "common.h"
#include <map>
#include <string>

using dtk_window = GLFWwindow;

namespace DTK {

    class Renderer {
    public:
        static void initialize();

    private:
        inline static std::map<const std::string, dtk_window *> windows;
        static void createWindow(const std::string &name);
    };

}// namespace DTK
