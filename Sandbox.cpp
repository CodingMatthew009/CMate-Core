
#include "Include/Clock.hpp"
#include "Include/DataEncrypter.hpp"
#include "Include/MLogger.hpp"
#include "Include/General/Enums.hpp"
#include "Include/Math/Vector2.hpp"
#include "Include/Math/Random.hpp"
#include "Include/SDataManager.hpp"

#include "Include/Math/ProceduralNoise/WhiteNoise.hpp"
#include "Include/Math/ProceduralNoise/ValueNoise.hpp"
#include "Include/Math/ProceduralNoise/PerlinNoise.hpp"
#include "Include/Math/ProceduralNoise/VoronoiNoise.hpp"

#include <thread>

using namespace cmate::core;
using namespace mathf;


double myDouble = 251.22943712;
int myInt = 52;
float myFloat = 23.42;
bool myBool = true;
std::string myString = "Hello My Friends";

Vector2 myVector = Vector2(2, 23);


int main(void)
{
    auto* local_clock = &cmate::core::Clock::Instance(); // DO NOT REMOVE, initializes class using current time, may be redone using a macro
    auto* sd_manager = &cmate::core::SDManager::Instance();
    Encrypter* save_encrypter = new Encrypter("Mates's Encryption Key");
    SET_LOGS_FOLDER("/home/mate/Projects/Mate-Utils/logs"); // KEEP AT THE TOP, some internal logs may break

    Noise::WhiteNoise myWhiteNoise(500, 100, true); // Also computed on the CPU but much less work
    Noise::ValueNoise myValueNoise(500, 512, 40, true); // Use carefully, computed on the CPU!!
    Noise::PerlinNoise myPerlinNoise(500, 512, 50, true);
    Noise::VoronoiNoise myVoronoiNoise(500, 512, 20, true);


    //Initiating savefile
    sd_manager->SetSaveFile("/home/mate/Projects/Mate-Utils/Save_File.odt");
    sd_manager->ClearSaveFile();

    LOG("-------------Initialized CMate-Core-------------", cmate::core::LFlags::INFO);

    myWhiteNoise.SaveAsImage("/home/mate/Projects/Mate-Utils/white_noise.bmp"); // Must be a .bmp file
    myValueNoise.SaveAsImage("/home/mate/Projects/Mate-Utils/value_noise.bmp"); // Must be a .bmp file
    myPerlinNoise.SaveAsImage("/home/mate/Projects/Mate-Utils/perlin_noise.bmp"); // Must be a .bmp file
    myVoronoiNoise.SaveAsImage("/home/mate/Projects/Mate-Utils/voronoi_noise.bmp"); // Must be a .bmp file

    int rand_int = Random::iRange(1, 100);
    int rand_int_seed = Random::iRangeS(1, 100, 412);

    double rand_double = Random::dRange(1, 100);
    double rand_double_seed = Random::dRangeS(1, 100, 412);

    std::string message = std::format("My random int is: {}, with seed {}.", rand_int, rand_int_seed);
    LOG(message, LFlags::INFO);


    message = std::format("My random double is: {}, with seed {}.", rand_double, rand_double_seed);
    LOG(message, LFlags::INFO);

    //Saving block
    {
        sd_manager->SaveData(myDouble, "myDouble"); //Name can be any string
        sd_manager->SaveData(myInt,    "myInt");
        sd_manager->SaveData(myFloat,  "myFloat");
        sd_manager->SaveData(myBool,   "myBool");
        sd_manager->SaveData(myString, "myString");
    
        // Always do after all saving has occured (Following data will be unencrypted)
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
