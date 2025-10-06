//
// Created by Yu Xin on 2025/10/1.
//

#include <iostream>
#include <loggermanger.h>
#include <loggerfactory.h>

using namespace std;
using namespace logger;

int main() {
    LoggerConfig config;
    config.logPath = "/Volumes/WD_BLACK/Coding/Project/CPP/Logger/logs/app.log";
    config.minLogLevel = LogLevel::DEBUG;
    config.type = LoggerType::SPDLOG;
    config.maxFileSize = 1024 * 1024;  // 1MB
    config.maxFiles = 5;
    config.asyncMode = true;
    config.consoleOutput = true;

    auto logger1 = LoggerFactory::createLogger(config);
    // 使用流式语法记录日志
    LOG_DEBUG(logger1) << "Debug message" << " with multiple " << "parts";
    LOG_INFO(logger1) << "Information: " << 42;
    LOG_WARN(logger1) << "Warning message";
    LOG_ERROR(logger1) << "Error occurred: " << "Something went wrong";

    // 修改日志级别
    logger1->setLogLevel(LogLevel::INFO);

    // Debug消息将不会被记录
    LOG_DEBUG(logger1) << "This debug message will not be logged";

    return 0;
}