//
// Created by travisdev on 7/23/23.
//
#include "Logger.h"

using namespace spdlog;

namespace DTK {
    void Logger::initialize() {
        logger = stdout_logger_mt("SYSTEM");
        set_default_logger(logger);
    }
} // DTK