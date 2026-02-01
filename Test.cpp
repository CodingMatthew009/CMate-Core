
#include "Include/Clock.hpp"
#include "Include/MLogger.hpp"
#include "Include/General/Enums.hpp"
#include "Include/Math/Vector2.hpp"
#include "Include/SDataManager.hpp"
#include <chrono>
#include <thread>

using namespace utils;
using namespace mathf;

int main(void)
{
    auto* local_clock = &utils::Clock::Instance(); // DO NOT REMOVE, initializes class using current time, may be redone using a macro

    local_clock->Sleep(std::chrono::milliseconds(2000));
    LOG("Initialized test script...", utils::LFlags::INFO);
    
    double myDouble = 251.22943712;
    int myInt = 52;
    float myFloat = 23.42;
    bool myBool = true;
    std::string myString = "Hello My Friends";

    //Initiating savefile
    SET_SAVE_FILE("/home/cmate/Documents/MateUtilities/Save_File.odt");
    

    //Saving data for each type
    
    utils::SDManager::Instance().SaveData(myDouble, GET_VARIABLE_NAME(myDouble));
    utils::SDManager::Instance().SaveData(myInt,    GET_VARIABLE_NAME(myInt));
    utils::SDManager::Instance().SaveData(myFloat,  GET_VARIABLE_NAME(myFloat));
    utils::SDManager::Instance().SaveData(myBool,   GET_VARIABLE_NAME(myBool));

    utils::SDManager::Instance().SaveData(myString,   GET_VARIABLE_NAME(myString));

    LOG("Saved Data to file!", LFlags::INFO);
    local_clock->Sleep(std::chrono::milliseconds(1000));
    LOG("Loading data!", LFlags::INFO);

    //Loading data based on name and type 
    
    auto loaded_int      = std::get<int>    (utils::SDManager::Instance().LoadData("int", "myInt"));
    auto loaded_float  = std::get<float>  (utils::SDManager::Instance().LoadData("float", "myFloat"));
    auto loaded_double= std::get<double> (utils::SDManager::Instance().LoadData("double", "myDouble"));
    auto loaded_bool     = std::get<int>    (utils::SDManager::Instance().LoadData("bool", "myBool"));

    auto loaded_string= std::get<std::string> (utils::SDManager::Instance().LoadData("string", "myString"));


    //Converting them to string (For Logging purpose)
    std::string converted_double = std::to_string(loaded_double);
    std::string converted_int    = std::to_string(loaded_int);
    std::string converted_float  = std::to_string(loaded_float);
    std::string converted_bool   = std::to_string(loaded_bool);

    std::string converted_string = loaded_string;

    //Logging using Macro
    LOG(converted_double, LFlags::INFO);
    LOG(converted_int,    LFlags::INFO);
    LOG(converted_float,  LFlags::INFO);
    LOG(converted_bool,   LFlags::INFO);
    
    LOG(loaded_string,   LFlags::INFO);

}