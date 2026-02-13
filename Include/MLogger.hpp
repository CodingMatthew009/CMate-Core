#pragma once
#include "./General/Enums.hpp"
#include "./General/Helpers.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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

            template<typename type>
            inline void Log(const type& message, LFlags logger_flag)
            {
                std::string time = FORMATTED_TIME_SINCE_START();
                std::string flag = format_flag(logger_flag);
                std::string message_str = helper::AnyToString(message);

                std::cout << time << " " << flag << message << std::endl;
        
                //Writing line to the logs folder
                std::ofstream log_stream;
                log_stream.open(current_file, std::ios::app);
                if (!log_stream) {std::cout << "Failed to open logs folder \n";}
                else 
                {
                    log_stream << time << " " << flag << message_str << std::endl;
                }
        
                current_entries.push_back(LogEntry({time, message_str, logger_flag}));
            }

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