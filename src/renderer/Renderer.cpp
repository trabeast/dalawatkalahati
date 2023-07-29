//
// Created by travisdev on 7/23/23.
//

#include "Renderer.h"
#include "Shader.h"
#include <stdexcept>

#define DTK_WINDOW_HEIGHT 1200
#define DTK_WINDOW_WIDTH 1600
#define DTK_OPENGL_MAJOR_VERSION 4
#define DTK_OPENGL_MINOR_VERSION 6

namespace DTK {
    void Renderer::initialize() {
        if(!glfwInit()) {
            throw std::runtime_error("Renderer Failed");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, DTK_OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, DTK_OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        createWindow(DTK_PRIMARY_WINDOW);

        auto primaryWindow = windows.at(DTK_PRIMARY_WINDOW);
        glfwMakeContextCurrent(primaryWindow);

        if(GLEW_OK != glewInit()) {
            throw new std::runtime_error("Renderer Failed");
        }

        glViewport(0, 0, DTK_WINDOW_WIDTH, DTK_WINDOW_HEIGHT);

        Shader *shader = new Shader;

        std::string fp = "./common.h";
        shader->create(VERTEX, fp);

        float vertices[] = {
                -0.5f, -0.5f,  0.0f,
                 0.5f, -0.5f,  0.0f,
                 0.0f,  0.5f,  0.0f
        };

        unsigned int VAO;
        unsigned int VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(vertices),
                     vertices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        const char *vertexShaderSource = "#version 460 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main() {\n"
                                         "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        }

        const char *fragmentShaderSource = "#version 460 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main() {\n"
                                           "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                           "}\0";
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        }

        unsigned int shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


        while (!glfwWindowShouldClose(primaryWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(primaryWindow);

            glfwPollEvents();
        }

        glfwTerminate();
    }

    void Renderer::createWindow(const std::string &name) {
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