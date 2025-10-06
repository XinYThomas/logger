//
// Created by Yu Xin on 2025/10/2.
//

#ifndef LOGGER_LOGGERFACTORY_H
#define LOGGER_LOGGERFACTORY_H

#include "loggermanger.h"
#include "spdlogmessage.h"

namespace logger {
    // 日志工厂类
    class LoggerFactory {
    public:
        static std::shared_ptr<LoggerBase> createLogger(const LoggerConfig& config);

    };
}

#endif //LOGGER_LOGGERFACTORY_H