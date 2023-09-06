//
// Created by travisdev on 7/23/23.
//

#include "Renderer.h"
#include "Buffer.h"
#include "Shader.h"
#include "ShaderProgram.h"

#define DTK_WINDOW_HEIGHT 600
#define DTK_WINDOW_WIDTH 800
#define DTK_OPENGL_MAJOR_VERSION 4
#define DTK_OPENGL_MINOR_VERSION 6
#define DTK_PRIMARY_WINDOW "primary"

namespace DTK {
    void Renderer::initialize() {
        if (!glfwInit()) {
            throw std::runtime_error("Renderer Failed");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, DTK_OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, DTK_OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        createWindow(DTK_PRIMARY_WINDOW);

        auto primaryWindow = windows.at(DTK_PRIMARY_WINDOW);
        glfwMakeContextCurrent(primaryWindow);

        if (GLEW_OK != glewInit()) {
            throw std::runtime_error("Renderer Failed");
        }

        glViewport(0, 0, DTK_WINDOW_WIDTH, DTK_WINDOW_HEIGHT);

        float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                            0.0f,  0.0f,  0.5f, 0.0f};

        unsigned int VAO;
        Buffer vbo;
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);

        vbo.bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              nullptr);
        glEnableVertexAttribArray(0);

        vbo.unbind();
        glBindVertexArray(0);

        Shader vertexShader(Shader::Type::VERTEX);
        Shader fragmentShader(Shader::Type::FRAGMENT);

        if (!vertexShader.compile("shaders/vertex.vert") ||
            !fragmentShader.compile("shaders/fragment.frag")) {
            abort();
        }

        ShaderProgram shaderProgram;

        shaderProgram.attachShader(vertexShader.shader);
        shaderProgram.attachShader(fragmentShader.shader);
        shaderProgram.link();

        while (!glfwWindowShouldClose(primaryWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);

            shaderProgram.use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(primaryWindow);

            glfwPollEvents();
        }

        glfwTerminate();
    }

    void Renderer::createWindow(const std::string &name) {
        windows.try_emplace(
                name, glfwCreateWindow(DTK_WINDOW_WIDTH, DTK_WINDOW_HEIGHT,
                                       name.c_str(), nullptr, nullptr));
    }
}// namespace DTK
