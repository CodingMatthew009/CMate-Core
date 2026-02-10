#pragma once

#include <string>
#include <format>

#include "TerminalColors.hpp"
namespace cmate::core
{
    //Flags for logger
    enum class LFlags {
        INFO,
        WARNING,
        ERROR,
        INSTALLED,
        FAILED,
        SUCCESS,
        UNDEFINED
    };

    //Returns formatted string of flag using colors
    inline std::string format_flag(LFlags flag)
    {
        std::string formatted_string;
        switch (flag) {
            case (LFlags::INFO):
            {
                formatted_string = std::format("[{}INFO{}]: ", BLUE, RESET);
                break;
            }
            case (LFlags::WARNING):
            {
                formatted_string = std::format("[{}WARNING{}]: ", YELLOW, RESET);
                break;
            }
            case (LFlags::ERROR):
            {
                formatted_string = std::format("[{}ERROR{}]: ", RED, RESET);
                break;
            }
            case (LFlags::INSTALLED):
            {
                formatted_string = std::format("[{}INSTALLED{}]: ", GREEN, RESET);
                break;
            }
            case (LFlags::FAILED):
            {
                formatted_string = std::format("[{}FAILED{}]: ", RED, RESET);
                break;
            }
            case (LFlags::SUCCESS):
            {
                formatted_string = std::format("[{}SUCCESS{}]: ", GREEN, RESET);
                break;
            }
            case (LFlags::UNDEFINED):
            {
                formatted_string = std::format("[{}UNDEFINED{}]: ", RESET, RESET);
                break;
            }
        }
        return formatted_string;
    }

}