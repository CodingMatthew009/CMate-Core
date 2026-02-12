#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <functional>

#include "General/Enums.hpp"

namespace cmate::core
{

    struct Timer
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

        template<typename time_type> double get_time()
        {
            auto duration = std::chrono::high_resolution_clock::now() - start_time;

            return std::chrono::duration_cast<time_type>(duration).count();
        }

        Timer();

        void reset_timer();
    };

    class PClock
    {
        public:
            static PClock& Instance();

            PClock(const PClock&) = delete;
            PClock &operator=(const PClock&) = delete;

            std::string get_formated_time_since_start() const;

            std::string get_formated_date_and_time() const;

            template<typename time_type> double get_time_since_start(time_type format)
            {
                auto duration = std::chrono::high_resolution_clock::now() - start_time;

                return std::chrono::duration_cast<format>(duration).count();
            }

            template<typename time_type> void Sleep(time_type time)
            {
                std::this_thread::sleep_for(time);
            }

            void reset_clock();

            std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
            std::chrono::time_point<std::chrono::high_resolution_clock> date;
        private:
            PClock();

    }; 

    //Macro for getting formatted runtime as a string
    #define FORMATTED_TIME_SINCE_START() \
        PClock::Instance().get_formated_time_since_start()

    #define FORMATTED_DATE_AND_TIME() \
        PClock::Instance().get_formated_date_and_time()
}