#include "../Include/MLogger.hpp"
#include "../Include/Clock.hpp"
#include <vector>
#include <iostream>

namespace utils
{
    Logger& Logger::Instance() 
    {
        static Logger instance;
        return instance;
    }

    void Logger::Log(std::string& message, LFlags logger_flag)
    {
        std::string time = FORMATTED_TIME_SINCE_START();
        std::string flag = format_flag(logger_flag);

        current_entries.push_back(LogEntry({time, message, logger_flag}));

        std::cout << time << " " << flag << message << std::endl;
    }

    void Logger::Log(const char* message, LFlags logger_flag)
    {
        std::string time = FORMATTED_TIME_SINCE_START();
        std::string flag = format_flag(logger_flag);

        current_entries.push_back(LogEntry({time, message, logger_flag}));

        std::cout << time << " " << flag << message << std::endl;       
    }

    std::vector<Logger::LogEntry> Logger::logs() const {
        return current_entries;
    }

    Logger::Logger() {};

}

