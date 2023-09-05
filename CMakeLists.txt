cmake_minimum_required(VERSION 3.25)
project(dalawatkalahati)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

set(DTK_SOURCES main.cpp
        src/logger/Logger.cpp
        src/renderer/Renderer.cpp
        src/renderer/Shader.cpp
        src/renderer/ShaderProgram.cpp
        src/renderer/Buffer.cpp)

set(DTK_HEADERS src/logger/
        src/renderer/
)

add_executable(dalawatkalahati ${DTK_SOURCES})

target_include_directories(dalawatkalahati PRIVATE ${CMAKE_SOURCE_DIR}/spdlog/include/ ${DTK_HEADERS})
target_link_libraries(dalawatkalahati PRIVATE ${CMAKE_SOURCE_DIR}/spdlog/build/libspdlog.a)
target_link_libraries(dalawatkalahati PRIVATE OpenGL::GL)
target_link_libraries(dalawatkalahati PRIVATE glfw)
target_link_libraries(dalawatkalahati PRIVATE GLEW::GLEW)
target_compile_definitions(dalawatkalahati PRIVATE SPDLOG_COMPILED_LIB)

set(DTK_RESOURCES shaders)
file(COPY ${DTK_RESOURCES} DESTINATION ${CMAKE_BINARY_DIR})
