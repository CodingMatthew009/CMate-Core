#pragma once
#include "./General/Enums.hpp"

#include <string>
#include <vector>

namespace utils 
{
    class Logger 
    {
        public:
            struct LogEntry {
                std::string timestamp;
                std::string message;
                LFlags log_flag;
            };

            static Logger& Instance();

            Logger(const Logger&) = delete;
            Logger &operator=(const Logger&) = delete;

            void Log(std::string& message, LFlags logger_flag);

            void Log(const char* message, LFlags logger_flag);

            std::vector<LogEntry> logs() const;

        private:
            Logger();

            std::vector<Logger::LogEntry> current_entries;

    };

    #define LOG(message, logger_flag) \
        Logger::Instance().Log(message, logger_flag)
}