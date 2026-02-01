
#include "Include/Clock.hpp"
#include "Include/DataEncrypter.hpp"
#include "Include/MLogger.hpp"
#include "Include/General/Enums.hpp"
#include "Include/Math/Vector2.hpp"
#include "Include/SDataManager.hpp"
#include <chrono>
#include <thread>

using namespace utils;
using namespace mathf;


double myDouble = 251.22943712;
int myInt = 52;
float myFloat = 23.42;
bool myBool = true;
std::string myString = "Hello My Friends";

int main(void)
{
    auto* local_clock = &utils::Clock::Instance(); // DO NOT REMOVE, initializes class using current time, may be redone using a macro
    auto* sd_manager = &utils::SDManager::Instance();
    Encrypter* save_encrypter = new Encrypter("Mates's Encryption Key");
    SET_LOGS_FOLDER("/home/cmate/Documents/MateUtilities/logs"); // KEEP AT THE TOP, some internal logs may break


    //Initiating savefile
    sd_manager->SetSaveFile("/home/cmate/Documents/MateUtilities/Save_File.odt");
    sd_manager->ClearSaveFile();

    LOG("-------------Initialized Mate's Utils-------------", utils::LFlags::INFO);


    //Saving block
    {
        sd_manager->SaveData(myDouble, GET_VARIABLE_NAME(myDouble)); //Name can be any string
        sd_manager->SaveData(myInt,    GET_VARIABLE_NAME(myInt));
        sd_manager->SaveData(myFloat,  GET_VARIABLE_NAME(myFloat));
        sd_manager->SaveData(myBool,   GET_VARIABLE_NAME(myBool));
        sd_manager->SaveData(myString, GET_VARIABLE_NAME(myString));
    
        // Always do after all saving has occured (Following data will be unencrypted)
        sd_manager->EncryptSaveFile(save_encrypter); 
    }

    LOG("Saved Data to file!", LFlags::INFO);
    local_clock->Sleep(std::chrono::milliseconds(1000));
    LOG("Loading data!", LFlags::INFO);

    std::string decrypted_data = sd_manager->DecryptSaveFile(save_encrypter);

    auto loaded_int      = std::get<int>    (sd_manager->LoadData(decrypted_data, "int", "myInt"));
    auto loaded_float  = std::get<float>  (sd_manager->LoadData(decrypted_data, "float", "myFloat"));
    auto loaded_double= std::get<double> (sd_manager->LoadData(decrypted_data, "double", "myDouble"));
    auto loaded_bool     = std::get<int>    (sd_manager->LoadData(decrypted_data, "bool", "myBool"));

    auto loaded_string= std::get<std::string> (sd_manager->LoadData(decrypted_data, "string", "myString"));


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

    local_clock->Sleep(std::chrono::seconds(2));


    /*Manual Encrypter test
    Encrypter* myEncrypter = new Encrypter("b210412bn");
    auto encrypted_data = myEncrypter->Encrypt("std::string Data");
    LOG(encrypted_data, LFlags::INFO);

    local_clock->Sleep(std::chrono::seconds(2));

    auto decrypted_data = myEncrypter->Decrypt(encrypted_data);
    LOG(decrypted_data, LFlags::INFO);*/
    delete local_clock;
    delete sd_manager;
    delete save_encrypter;
}
