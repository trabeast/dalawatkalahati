//
// Created by travisdev on 7/23/23.
//

#include "Renderer.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include <stdexcept>

#define DTK_WINDOW_HEIGHT 600
#define DTK_WINDOW_WIDTH 800
#define DTK_OPENGL_MAJOR_VERSION 4
#define DTK_OPENGL_MINOR_VERSION 6

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
        unsigned int VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shader_t vertexShader = Shader::create(Shader::Type::VERTEX);
        shader_t fragmentShader = Shader::create(Shader::Type::FRAGMENT);

        if (!Shader::compile(vertexShader, "shaders/vertex.vert") ||
            !Shader::compile(fragmentShader, "shaders/fragment.frag")) {
            throw std::runtime_error("Shader compilation failed");
        }

        shader_program_t shaderProgram = ShaderProgram::create();

        ShaderProgram::attachShader(shaderProgram, vertexShader);
        ShaderProgram::attachShader(shaderProgram, fragmentShader);
        ShaderProgram::link(shaderProgram);

        Shader::destroy(vertexShader);
        Shader::destroy(fragmentShader);


        while (!glfwWindowShouldClose(primaryWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);

            ShaderProgram::use(shaderProgram);
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