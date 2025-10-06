//
// Created by Yu Xin on 2025/9/27.
//

#include "spdlogmessage.h"
using namespace logger;

void SpdLogger::initialize() {
    std::vector<spdlog::sink_ptr> sinks;

    // 文件
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        config_.logPath,
        config_.maxFileSize,
        config_.maxFiles
    );
    sinks.push_back(file_sink);
    // 控制台
    if (config_.consoleOutput) {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sinks.push_back(console_sink);
    }

    // 创建
    if (config_.asyncMode) {
        spdlog::init_thread_pool(8192, 1);
        logger_ = std::make_shared<spdlog::async_logger>(
            "async_logger",
            sinks.begin(),
            sinks.end(),
            spdlog::thread_pool(),
            spdlog::async_overflow_policy::overrun_oldest
            );
    } else {
        logger_ = std::make_shared<spdlog::logger>("sync_logger", sinks.begin(), sinks.end());
    }

    setPattern(config_.pattern);

    logger_->set_level(convertLevel(config_.minLogLevel));
}

spdlog::level::level_enum SpdLogger::convertLevel(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:
            return spdlog::level::debug;
        case LogLevel::INFO:
            return spdlog::level::info;
        case LogLevel::WARNING:
            return spdlog::level::warn;
        case LogLevel::ERROR:
            return spdlog::level::err;
        case LogLevel::FATAL:
            return spdlog::level::critical;
        default:
            return spdlog::level::info;
    }
}

void SpdLogger::setPattern(const std::string &pattern) {
    logger_->set_pattern(pattern);
}

void SpdLogger::reconfigure() {
    initialize();
}

void SpdLogger::flush() {
    logger_->flush();
}

void SpdLogger::log(const LogMessage& message) {
    if (!shouldLog(message.level())) {
        return;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    switch (message.level()) {
        case LogLevel::DEBUG:
            logger_->debug(message.str());
            break;
        case LogLevel::INFO:
            logger_->info(message.str());
            break;
        case LogLevel::WARNING:
            logger_->warn(message.str());
            break;
        case LogLevel::ERROR:
            logger_->error(message.str());
            break;
        case LogLevel::FATAL:
            logger_->critical(message.str());
            break;
    }
}

