//
// Created by travisdev on 7/23/23.
//
#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/logger.h>

using dtk_logger = std::shared_ptr<spdlog::logger>;
using dtk_logger_level = spdlog::level::level_enum;

namespace DTK {

    class Logger {
    public:
        enum class LEVEL {
            TRACE = SPDLOG_LEVEL_TRACE,
            DEBUG = SPDLOG_LEVEL_DEBUG,
            INFO = SPDLOG_LEVEL_INFO,
            WARN = SPDLOG_LEVEL_WARN,
            ERROR = SPDLOG_LEVEL_ERROR,
            FATAL = SPDLOG_LEVEL_CRITICAL
        };

        static void initialize();

        template<typename T>
        static void log(LEVEL level, const T &value) {
            if(level < activeLevel) return;
            logger->log(static_cast<dtk_logger_level>(level), value);
        }
    private:
        inline static dtk_logger logger;
        inline static LEVEL activeLevel = LEVEL::INFO;
    };

} // DTK
