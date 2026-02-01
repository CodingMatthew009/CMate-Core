#pragma once

#include <chrono>
#include <string>

namespace utils
{
    class Clock
    {
        public:
            static Clock& Instance();

            Clock(const Clock&) = delete;
            Clock &operator=(const Clock&) = delete;

            std::string get_formated_time_since_start();

            void reset_time();

            std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
        private:
            Clock();

    }; 

    //Macro for getting formatted runtime as a string
    #define FORMATTED_TIME_SINCE_START() \
        Clock::Instance().get_formated_time_since_start()

    //Macro for resetting the runtime
    #define RESET_TIME() \
        Clock::Instance().reset_time()
}