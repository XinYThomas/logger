//
// Created by Yu Xin on 2025/9/27.
//

#ifndef LOGGER_SPDLOGMESSAGE_H
#define LOGGER_SPDLOGMESSAGE_H

#include "loggermanger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>

namespace logger {
    class SpdLogger : public LoggerBase {
    public:
        explicit SpdLogger(const LoggerConfig &config) : LoggerBase(config) {
            SpdLogger::initialize();
        }

        void initialize() override;
        void log(const LogMessage &message) override;
        void flush() override;
        void setPattern(const std::string &pattern) override;

    protected:
        void reconfigure() override;

    private:
        std::shared_ptr<spdlog::logger> logger_;

        spdlog::level::level_enum convertLevel(LogLevel level);
    };
}


#endif //LOGGER_SPDLOGMESSAGE_H