#pragma once
#include "./General/Enums.hpp"

#include <string>
#include <vector>

namespace utils 
{
    class Logger 
    {
        public:
            //Struct for storing entry data
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

            //Returns vector of logs 
            std::vector<LogEntry> logs() const;

        private:
            Logger();

            //Private list of all entries
            std::vector<Logger::LogEntry> current_entries;

    };

    //Macro for logging 
    #define LOG(message, logger_flag) \
        Logger::Instance().Log(message, logger_flag)
}