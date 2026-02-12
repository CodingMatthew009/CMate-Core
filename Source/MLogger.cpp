#include "../Include/CMate-Core.h"

#include <vector>

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
        current_file = logs_path + "/" + FORMATTED_DATE_AND_TIME() + ".txt";
    }

    std::vector<Logger::LogEntry> Logger::logs() const {
        return current_entries;
    }

    Logger::Logger() {};

}

