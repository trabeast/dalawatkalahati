//
// Created by travisdev on 7/23/23.
//
#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace spdlog;

namespace DTK {
    void Logger::initialize() {
        console = stdout_color_mt("console");
        set_default_logger(console);
    }
}// namespace DTK