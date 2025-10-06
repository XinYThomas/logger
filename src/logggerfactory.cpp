//
// Created by Yu Xin on 2025/10/2.
//

#include "loggerfactory.h"

using namespace logger;

std::shared_ptr<LoggerBase> LoggerFactory::createLogger(const LoggerConfig &config) {
    switch (config.type) {
        case LoggerType::SPDLOG:
            return std::make_shared<SpdLogger>(config);
        default:
            throw std::runtime_error("Unsupported logger type");
    }
}
