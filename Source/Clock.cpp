#include "../Include/Clock.hpp"
#include <chrono>
#include <ctime>
#include <format>
#include <string>

namespace cmate::core
{

    Timer::Timer() {
        reset_timer();
    }

    void Timer::reset_timer()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }


    PClock& PClock::Instance()
    {
        static PClock instance;
        return instance;
    }

    std::string PClock::get_formated_time_since_start() const
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

    std::string PClock::get_formated_date_and_time() const
    {
        auto date = std::chrono::system_clock::now();
        auto time_to_date = std::chrono::system_clock::to_time_t(date);
        std::string string_date = (ctime(&time_to_date));

        return string_date;
    }

    void PClock::reset_clock() 
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    PClock::PClock() {
        reset_clock();
    }
}