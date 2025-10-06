//
// Created by Yu Xin on 2025/9/27.
//

#ifndef LOGGER_LOGGERMANGER_H
#define LOGGER_LOGGERMANGER_H

#include <string>
#include <sstream>

#define LOG_DEBUG(loggerMethod) loggerMethod->createLogMessage(logger::LogLevel::DEBUG, __FILE_NAME__, __LINE__)
#define LOG_INFO(loggerMethod) loggerMethod->createLogMessage(logger::LogLevel::INFO, __FILE_NAME__, __LINE__)
#define LOG_WARN(loggerMethod) loggerMethod->createLogMessage(logger::LogLevel::WARNING, __FILE_NAME__, __LINE__)
#define LOG_ERROR(loggerMethod) loggerMethod->createLogMessage(logger::LogLevel::ERROR, __FILE_NAME__, __LINE__)
#define LOG_FATAL(loggerMethod) loggerMethod->createLogMessage(logger::LogLevel::FATAL, __FILE_NAME__, __LINE__)

using namespace std;

namespace logger {
    enum LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    enum class LoggerType {
        SPDLOG,
        GLOG
    };

    struct LoggerConfig {
        std::string logPath;
        LogLevel minLogLevel;
        LoggerType type;
        size_t maxFileSize;            // 单个日志文件最大大小（字节）
        size_t maxFiles;               // 最大日志文件数量
        bool asyncMode;                // 是否使用异步模式
        bool consoleOutput;            // 是否输出到控制台
        std::string pattern;           // 日志格式模式

        LoggerConfig() :
            minLogLevel(LogLevel::DEBUG),
            type(LoggerType::SPDLOG),
            maxFileSize(5 * 1024 * 1024),  // 默认5MB
            maxFiles(10),
            asyncMode(true),
            consoleOutput(true),
            pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] %v") {}
    };

    class LoggerBase;

    class LogMessage {
        public:
            LogMessage(LoggerBase* loggerMethod, LogLevel level,
                const char* file = __FILE_NAME__, int line = __LINE__) :
                level_(level), loggerMethod_(loggerMethod) {
                stream_ << "[" << file << ":" << line << "] ";
            }

            ~LogMessage();

            template <typename T>
                LogMessage& operator<<(const T& msg) {
                stream_ << msg;
                return *this;
            }

            std::string str() const {return stream_.str();}
            LogLevel level() const {return level_;}

        private:
            LoggerBase* loggerMethod_;
            ostringstream stream_;
            LogLevel level_;
    };

    class LoggerBase {
    public:
        explicit LoggerBase(const LoggerConfig& config) : config_(config) {}
        virtual ~LoggerBase() = default;

        virtual void initialize() = 0;
        virtual void log(const LogMessage& message) = 0;
        virtual void flush() = 0;
        virtual void setPattern(const std::string& pattern) = 0;

        bool shouldLog(LogLevel level) const {
            return level >= config_.minLogLevel;
        }

        // 便捷日志方法
        LogMessage createLogMessage(LogLevel level, const char* file, int line) {
            return LogMessage(this, level, file, line);
        }

        // 获取配置
        const LoggerConfig& getConfig() const { return config_; }

        // 修改配置
        void setConfig(const LoggerConfig& config) {
            config_ = config;
            reconfigure();
        }

        // 设置日志级别
        void setLogLevel(LogLevel level) {
            config_.minLogLevel = level;
            reconfigure();
        }

    protected:
        LoggerConfig config_;
        std::mutex mutex_;
        virtual void reconfigure() = 0;
    };

    inline LogMessage::~LogMessage() {
        if (loggerMethod_) {
            loggerMethod_->log(*this);
        }
    }

}



#endif //LOGGER_LOGGERMANGER_H