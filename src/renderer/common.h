//
// Created by travisdev on 7/29/23.
//

#pragma once

#include "Logger.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void CheckOpenGLError(const char *stmt, const char *fname, int line) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        DTK_LOGGER_ERROR("OpenGL error {}, at {}:{} - for {}\n", err, fname,
                         line, stmt);
        abort();
    }
}

#ifndef GL_CHECK
#define GL_CHECK(stmt)                                                         \
    do {                                                                       \
        stmt;                                                                  \
        CheckOpenGLError(#stmt, __FILE__, __LINE__);                           \
    } while (0)
#endif