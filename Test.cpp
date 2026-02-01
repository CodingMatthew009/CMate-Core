
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
    auto* sd_manager = &utils::SDManager::Instance();

    local_clock->Sleep(std::chrono::milliseconds(2000));
    LOG("Initialized test script...", utils::LFlags::INFO);
    
    double myDouble = 251.22943712;
    int myInt = 52;
    float myFloat = 23.42;
    bool myBool = true;
    std::string myString = "Hello My Friends";

    //Initiating savefile
    sd_manager->SetSaveFile("/home/cmate/Documents/MateUtilities/Save_File.odt");
    sd_manager->ClearSaveFile();

    //Saving data for each type
    
    sd_manager->SaveData(myDouble, GET_VARIABLE_NAME(myDouble));
    sd_manager->SaveData(myInt,    GET_VARIABLE_NAME(myInt));
    sd_manager->SaveData(myFloat,  GET_VARIABLE_NAME(myFloat));
    sd_manager->SaveData(myBool,   GET_VARIABLE_NAME(myBool));

    sd_manager->SaveData(myString,   GET_VARIABLE_NAME(myString));

    LOG("Saved Data to file!", LFlags::INFO);
    local_clock->Sleep(std::chrono::milliseconds(1000));
    LOG("Loading data!", LFlags::INFO);

    //Loading data based on name and type 
    
    auto loaded_int      = std::get<int>    (sd_manager->LoadData("int", "myInt"));
    auto loaded_float  = std::get<float>  (sd_manager->LoadData("float", "myFloat"));
    auto loaded_double= std::get<double> (sd_manager->LoadData("double", "myDouble"));
    auto loaded_bool     = std::get<int>    (sd_manager->LoadData("bool", "myBool"));

    auto loaded_string= std::get<std::string> (sd_manager->LoadData("string", "myString"));


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