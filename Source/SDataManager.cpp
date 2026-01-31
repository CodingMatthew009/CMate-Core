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

    SDManager::types SDManager::LoadData(std::string data_type, std::string data_name)
    {
        std::ifstream infile(file_path);
        if (!infile)
        {
            LOG("Failed to open SaveFile", LFlags::ERROR);
        } 
    
        std::string line;
        while(std::getline(infile, line))
        {
            std::istringstream iss(line);
            std::string name;
            std::string type;
            iss >> name >> type;

            if(name == data_name && type == data_type)
            {
                std::string value;

                iss >> value;

                auto uType = types();
                if (data_type == "double")
                {
                    uType._double = std::stod(value);
                }
                if (data_type == "int")
                {
                    uType._int = std::stoi(value);
                }
                if (data_type == "float")
                {
                    uType._float = std::stof(value);
                }
                if (data_type == "bool")
                {
                    uType._bool = std::stoi(value);
                }
                infile.close();
                return uType;
            }
        }

        auto message = std::format("Couldn't find Data with the name: {} of type : {}", data_name, data_type);
        LOG(message, LFlags::ERROR);
        return types();
    }

    SDManager::SDManager() {};
}
