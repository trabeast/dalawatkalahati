//
// Created by travisdev on 7/23/23.
//
#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#define DTK_LOGGER_INFO(...) DTK::Logger::console->info(__VA_ARGS__)
#define DTK_LOGGER_ERROR(...) DTK::Logger::console->error(__VA_ARGS__)

namespace DTK {
    using logger_t = std::shared_ptr<spdlog::logger>;

    class Logger {
    public:
        static void initialize();
        inline static logger_t console;
    };

}// namespace DTK
