#pragma once

#include <string>
#include <format>
#include <iostream>

#include "Colors.hpp"
namespace utils
{
    enum class LFlags {
        INFO,
        WARNING,
        ERROR,

        UNDEFINED
    };

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