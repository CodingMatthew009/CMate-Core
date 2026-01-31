
#include "Include/Clock.hpp"
#include "Include/MLogger.hpp"
#include "Include/General/Enums.hpp"
#include "Include/Math/Vector2.hpp"
#include <chrono>
#include <thread>

using namespace utils;
using namespace mathf;
int main(void)
{
    utils::Clock::Instance(); // DO NOT REMOVE, initializes class using current time

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    LOG("Initialized logging...", utils::LFlags::INFO);
    Vector2 myVector = Vector2(0, 9);
    Vector3 myVector3 = Vector3(0, 4, 2);

}