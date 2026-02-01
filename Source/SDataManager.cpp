#include "../Include/SDataManager.hpp"
#include "../Include/General/Enums.hpp"
#include <fstream>
#include <string>

namespace utils
{
    SDManager& SDManager::Instance() 
    {
        static SDManager instance;
        return instance;
    }

    void SDManager::SetSaveFile(std::string path)
    {
        file_path = path;
    }

    void SDManager::SetSaveFile(const char* path)
    {
        file_path = path;
    }

    SDManager::types SDManager::LoadData(std::string data_type, std::string data_name) const
    {
        std::ifstream infile(file_path); 
        if (!infile)
        {
            LOG("Failed to open SaveFile", LFlags::FAILED);
        } 
    
        std::string line;
        while(std::getline(infile, line)) //Go through each line the stream
        {
            std::istringstream iss(line); //Parse the line into words
            std::string name;
            std::string type;
            iss >> name >> type; //Output fist word to name, second to type

            if(name == data_name && type == data_type)
            {
                std::string value;

                iss >> value;

                auto _types = types();
                if (data_type == "double")
                {
                    _types = std::stod(value);
                }
                if (data_type == "int")
                {
                    _types = std::stoi(value);
                }
                if (data_type == "float")
                {
                   _types = std::stof(value);
                }
                if (data_type == "bool")
                {
                    _types = std::stoi(value);
                }
                if (data_type == "string")
                {
                    _types = helper::strReplace(value, '~', ' ');
                }
                infile.close();
                std::string message = std::format("Successfully loaded {} from: {}", data_name, file_path);
                LOG(message, LFlags::SUCCESS);
                return _types;
            }
        }

        auto message = std::format("Couldn't find Data with the name: {} of type : {}", data_name, data_type);
        LOG(message, LFlags::ERROR);
        return types();
    }

    SDManager::SDManager() {};
}
