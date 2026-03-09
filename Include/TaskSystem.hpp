#pragma once

#include <chrono>
#include <thread>
#include <functional>
#include "Clock.hpp"

namespace cmate::core 
{
    class Task 
    {
        protected:
        bool started = false;
        std::thread task_thread;

        public:
        Task() {};
        void start_task()  {started = true;}
        virtual void join_task()   {if (task_thread.joinable()) task_thread.join();}
        virtual void detach_task() {task_thread.detach();}
    };

    class TaskManager
    {
        private:
        std::vector<Task> active_tasks;

        public:
        Task find_task(std::string& name);
        void join_all_tasks();
        void detach_all_tasks();
    };

    // Class for executing function after n time (may be relocated)
    class TimedTask : public Task
    {
        public:
        template<typename time_type> 
        TimedTask(const char* name, time_type time, std::function<void()> function)
        {
            long time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();

            task_thread = std::thread([time_ms, this, function] {
                if (time_ms != 0)
                {
                    Timer task_timer = Timer();

                    while ((task_timer.get_time<std::chrono::milliseconds>() < time_ms))
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));

                        if (started) break;
                    }
                }
                else
                {
                    while (!started)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                }

                function();
            });
        }
    };
}