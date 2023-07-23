cmake_minimum_required(VERSION 3.25)
project(dalawatkalahati)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set(DTK_SOURCES main.cpp
        src/logger/Logger.cpp
        src/renderer/Renderer.cpp)

add_executable(dalawatkalahati ${DTK_SOURCES})

target_include_directories(dalawatkalahati PRIVATE ${CMAKE_SOURCE_DIR}/spdlog/include/)
target_link_libraries(dalawatkalahati PRIVATE ${CMAKE_SOURCE_DIR}/spdlog/build/libspdlog.a)
target_link_libraries(dalawatkalahati PRIVATE glfw)
target_link_libraries(dalawatkalahati PRIVATE OpenGL::GL)
target_compile_definitions(dalawatkalahati PRIVATE SPDLOG_COMPILED_LIB)
