#include "../Include/Clock.hpp"
#include <chrono>
#include <format>

namespace utils
{
    Clock& Clock::Instance()
    {
        static Clock instance;
        return instance;
    }

    std::string Clock::get_formated_time_since_start() const
    {
        auto duration = std::chrono::high_resolution_clock::now() - start_time;

        auto hours = std::chrono::duration_cast<std::chrono::hours> (duration);
        duration - hours;

        auto minutes = std::chrono::duration_cast<std::chrono::minutes> (duration);
        duration - minutes;

        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        
        std::string formatted_string = std::format("[{}H:{}M:{}S]", hours.count(), minutes.count(), seconds.count());
        return formatted_string;
    }

    void Clock::reset_time() 
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    Clock::Clock() {
        reset_time();
    }
}