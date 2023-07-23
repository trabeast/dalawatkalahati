//
// Created by travisdev on 7/23/23.
//

#include "Renderer.h"
#include <stdexcept>

#define DTK_WINDOW_HEIGHT 480
#define DTK_WINDOW_WIDTH 640
#define DTK_OPENGL_MAJOR_VERSION 4
#define DTK_OPENGL_MINOR_VERSION 6

namespace DTK {
    void Renderer::initialize() {
        if(!glfwInit()) {
            throw std::runtime_error("Renderer Failed");
        }

        setOpenGlVersion(DTK_OPENGL_MAJOR_VERSION, DTK_OPENGL_MINOR_VERSION);
        createWindow(DTK_PRIMARY_WINDOW);
    }

    void Renderer::setOpenGlVersion(const int majorVersion, const int minorVersion) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    }

    void Renderer::createWindow(const std::string name) {
        windows.try_emplace(
                name,
                glfwCreateWindow(
                        DTK_WINDOW_WIDTH,
                        DTK_WINDOW_HEIGHT,
                        name.c_str(),
                        nullptr,
                        nullptr)
        );
    }
} // DTK