//
// Created by travisdev on 8/4/23.
//

#pragma once
#include "common.h"
#include <functional>
#include <stdexcept>
#include <vector>

#define DTK_LOG_SIZE 512

#define DTK_COMPILE_STATUS GL_COMPILE_STATUS
#define DTK_LINK_STATUS GL_LINK_STATUS

namespace DTK {
    class LogChecker {
    protected:
        // ShaderType can be either a shader or a program.

        template<typename ShaderType>
        using gl_param_getter_t =
                std::function<void(ShaderType, unsigned int, int *)>;

        template<typename ShaderType>
        using gl_info_log_t =
                std::function<void(ShaderType, int, int *, char *)>;

        template<typename ShaderType>
        static bool check(ShaderType shaderObj, unsigned int status,
                          gl_param_getter_t<ShaderType> getter,
                          gl_info_log_t<ShaderType> infoLog) {
            int success;
            std::vector<char> log(DTK_LOG_SIZE);
            int length;
            GL_CHECK(getter(shaderObj, status, &success));
            if (!success) {
                GL_CHECK(infoLog(shaderObj, DTK_LOG_SIZE, &length, &log[0]));
                DTK_LOGGER_ERROR("{}", log.data());
                return false;
            }

            return true;
        }
    };
}// namespace DTK