#pragma once
#include "./General/Enums.hpp"

#include <string>
#include <vector>

namespace cmate::core 
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

            void SetLogsFolder(std::string path);

            void Log(std::string& message, LFlags logger_flag=LFlags::UNDEFINED);

            void Log(const char* message, LFlags logger_flag=LFlags::UNDEFINED);

            //Returns vector of logs 
            std::vector<LogEntry> logs() const;

        private:
            Logger();

            std::string logs_path;

            std::string current_file;

            //Private list of all entries
            std::vector<Logger::LogEntry> current_entries;

    };

    //Macro for logging 
    #define LOG(message, logger_flag) \
        Logger::Instance().Log(message, logger_flag)

    #define SET_LOGS_FOLDER(path) \
        Logger::Instance().SetLogsFolder(path)
}