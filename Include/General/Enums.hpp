#pragma once

#include <string>
#include <format>

#include "Colors.hpp"
namespace utils
{
    //Flags for logger
    enum class LFlags {
        INFO,
        WARNING,
        ERROR,
        //ISTALLED
        //FAILED,
        //SUCCESS,
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
            case (LFlags::UNDEFINED):
            {
                formatted_string = std::format("[{}UNDEFINED{}]: ", RESET, RESET);
                break;
            }
        }
        return formatted_string;
    }

}