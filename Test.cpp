
#include "Include/Clock.hpp"
#include "Include/MLogger.hpp"
#include "Include/General/Enums.hpp"
#include "Include/Math/Vector2.hpp"
#include "Include/SDataManager.hpp"
#include <any>
#include <chrono>
#include <thread>

using namespace utils;
using namespace mathf;
int main(void)
{
    utils::Clock::Instance(); // DO NOT REMOVE, initializes class using current time, may be redone using a macro

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    LOG("Initialized logging...", utils::LFlags::INFO);
    
    double myDouble = 251.22943712;
    int myInt = 52;
    float myFloat = 23.42;
    bool myBool = true;

    //Initiating savefile, will be redone with macro
    utils::SDManager::Instance().SetSaveFile("/home/cmate/Documents/MateUtilities/Save_File.odt");
    

    //Saving data for each type
    utils::SDManager::Instance().SaveData(myDouble, GET_VARIABLE_NAME(myDouble));
    utils::SDManager::Instance().SaveData(myInt,    GET_VARIABLE_NAME(myInt));
    utils::SDManager::Instance().SaveData(myFloat,  GET_VARIABLE_NAME(myFloat));
    utils::SDManager::Instance().SaveData(myBool,   GET_VARIABLE_NAME(myBool));

    //Loading data based on name and type
    auto loaded_int    = utils::SDManager::Instance().LoadData("int", "myInt");
    auto loaded_float  = utils::SDManager::Instance().LoadData("float", "myFloat");
    auto loaded_double = utils::SDManager::Instance().LoadData("double", "myadDouble");
    auto loaded_bool   = utils::SDManager::Instance().LoadData("bool", "myBool");

    //Converting them to string (For Logging purpose)
    auto converted_double = std::to_string(loaded_double._double);
    auto converted_int    = std::to_string(loaded_int._int);
    auto converted_float  = std::to_string(loaded_float._float);
    auto converted_bool   = std::to_string(loaded_bool._bool);

    //Logging using Macro
    LOG(converted_double, LFlags::INFO);
    LOG(converted_int,    LFlags::INFO);
    LOG(converted_float,  LFlags::INFO);
    LOG(converted_bool,   LFlags::INFO);


}