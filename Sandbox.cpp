
#include "Include/CMate-Core.h"

#include <charconv>
#include <thread>

using namespace cmate::core;
using namespace mathf;


double myDouble = 251.22943712;
int myInt = 52;
float myFloat = 23.42;
bool myBool = true;
std::string myString = "Hello My Friends";


int main(void)
{
    auto* local_clock = &cmate::core::PClock::Instance(); // DO NOT REMOVE, initializes class using current time, may be redone using a macro
    auto* sd_manager = &cmate::core::SDManager::Instance();
    Encrypter* save_encrypter = new Encrypter("Mates's Encryption Key");
    SET_LOGS_FOLDER("/home/mate/Projects/Mate-Utils/logs"); // KEEP AT THE TOP, some internal logs may break

    //Initiating savefile
    sd_manager->SetSaveFile("/home/mate/Projects/Mate-Utils/Save_File.odt");
    sd_manager->ClearSaveFile();

    LOG("-------------Initialized CMate-Core-------------", cmate::core::LFlags::INFO);



    /*TimedTask myTask("myTask", std::chrono::seconds(10), [] { 
        LOG("Executed task!", LFlags::SUCCESS);
    });*/

    //Saving block
    {
        sd_manager->SaveData(myDouble, "myDouble"); //Name can be any string
        sd_manager->SaveData(myInt,    "myInt");
        sd_manager->SaveData(myFloat,  "myFloat");
        sd_manager->SaveData(myBool,   "myBool");
        sd_manager->SaveData(myString, "myString");
    
        int x = 5;
        std::string yomama = "fuck of ";
        sd_manager->SaveDataBlock("MyVector", x, yomama);

        sd_manager->EncryptSaveFile(save_encrypter); 
    }

    LOG("Saved Data to file!", LFlags::INFO);
    local_clock->Sleep(std::chrono::milliseconds(1000));
    LOG("Loading data!", LFlags::INFO);

    std::string decrypted_data = sd_manager->DecryptSaveFile(save_encrypter);

    auto loaded_int      = std::get<int>    (sd_manager->LoadData(decrypted_data, "int", "myInt"));
    auto loaded_float    = std::get<float>  (sd_manager->LoadData(decrypted_data, "float", "myFloat"));
    auto loaded_double   = std::get<double> (sd_manager->LoadData(decrypted_data, "double", "myDouble"));
    auto loaded_bool     = std::get<int>    (sd_manager->LoadData(decrypted_data, "bool", "myBool"));

    auto loaded_string   = std::get<std::string> (sd_manager->LoadData(decrypted_data, "string", "myString"));

    auto loaded_data_block = sd_manager->LoadDataBlock(decrypted_data, "MyVector");

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

    for (auto _data : loaded_data_block)
    {
        std::string converted_data = helper::GetDataFromVariant(_data);
        LOG(converted_data, LFlags::INFO);
    }

    local_clock->Sleep(std::chrono::seconds(2));

    LOG("Manual Encryption Test", LFlags::INFO);
    //Manual Encrypter test
    Encrypter myEncrypter = Encrypter("b210412bn");
    auto encrypted_string = myEncrypter.Encrypt("std::string Data");
    local_clock->Sleep(std::chrono::seconds(2));
    auto decrypted_string = myEncrypter.Decrypt(encrypted_string);

    //Finnish Sandbox
    delete save_encrypter;
    return 0;
}
