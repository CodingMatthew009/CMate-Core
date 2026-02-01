#pragma once

#include <chrono>
#include <string>
#include <thread>

namespace utils
{
    class Clock
    {
        public:
            static Clock& Instance();

            Clock(const Clock&) = delete;
            Clock &operator=(const Clock&) = delete;

            std::string get_formated_time_since_start() const;

            template<typename T> void Sleep(T duration)
            {
                std::this_thread::sleep_for(duration);
            }

            void reset_time();

            std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
            std::chrono::time_point<std::chrono::high_resolution_clock> date;
        private:
            Clock();

    }; 

    //Macro for getting formatted runtime as a string
    #define FORMATTED_TIME_SINCE_START() \
        Clock::Instance().get_formated_time_since_start()
}