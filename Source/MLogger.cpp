#include "../Include/MLogger.hpp"
#include "../Include/Clock.hpp"
#include <vector>
#include <iostream>
#include <fstream>

namespace cmate::core
{
    Logger& Logger::Instance() 
    {
        static Logger instance;
        return instance;
    }

    void Logger::SetLogsFolder(std::string path)
    {
        logs_path = path;
        current_file = logs_path + "/" + FORMATTED_DATE_AND_TIME_SINCE_START() + ".txt";
    }

    void Logger::Log(std::string& message, LFlags logger_flag)
    {
        std::string time = FORMATTED_TIME_SINCE_START();
        std::string flag = format_flag(logger_flag);

        std::cout << time << " " << flag << message << std::endl;

        //Writing line to the logs folder
        std::ofstream log_stream;
        log_stream.open(current_file, std::ios::app);
        if (!log_stream) {std::cout << "Failed to open logs folder \n";}
        else 
        {
            log_stream << time << " " << flag << message << std::endl;
        }

        current_entries.push_back(LogEntry({time, message, logger_flag}));
    }

    void Logger::Log(const char* message, LFlags logger_flag)
    {
        std::string time = FORMATTED_TIME_SINCE_START();
        std::string flag = format_flag(logger_flag);

        std::cout << time << " " << flag << message << std::endl;

        //Writing line to the logs folder
        std::ofstream log_stream;
        log_stream.open(current_file, std::ios::app);
        if (!log_stream) {std::cout << "Failed to open logs folder \n";}
        else 
        {
            log_stream << time << " " << flag << message << std::endl;
        }

        current_entries.push_back(LogEntry({time, message, logger_flag}));  
    }

    std::vector<Logger::LogEntry> Logger::logs() const {
        return current_entries;
    }

    Logger::Logger() {};

}

