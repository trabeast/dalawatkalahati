//
// Created by travisdev on 8/4/23.
//

#pragma once
#include "Logger.h"
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
        template<typename ShaderObj>
        using gl_param_getter_t =
                std::function<void(ShaderObj, unsigned int, int *)>;

        template<typename ShaderObj>
        using gl_info_log_t =
                std::function<void(ShaderObj, int, int *, char *)>;

        template<typename ShaderObj>
        static bool check(ShaderObj shaderObj, unsigned int status,
                          gl_param_getter_t<ShaderObj> getter,
                          gl_info_log_t<ShaderObj> infoLog) {
            int success;
            std::vector<char> log(DTK_LOG_SIZE);
            int length;
            getter(shaderObj, status, &success);
            if (!success) {
                infoLog(shaderObj, DTK_LOG_SIZE, &length, &log[0]);
                DTK_LOGGER_ERROR("{}", log.data());
                return false;
            }

            return true;
        }
    };
}// namespace DTK