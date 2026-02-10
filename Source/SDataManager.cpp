#include "../Include/SDataManager.hpp"

namespace cmate::core
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

    void SDManager::ClearSaveFile() const
    {
        std::ofstream output_stream;

        //Clear saved data
        output_stream.open(file_path, std::ios::out);
        output_stream << "";
        output_stream.close();

        LOG("Cleared all data inside the save file.", LFlags::INFO);
    }

    void SDManager::EncryptSaveFile(Encrypter* encrypter) const
    {
        std::ifstream input_stream;
        std::ofstream output_stream;

        std::string plain_data;
        std::stringstream buffer; // Buffer of characters from whole file

        input_stream.open(file_path, std::ios::binary);
        if (!input_stream) {LOG("Failed to open save file for encryption", LFlags::FAILED);}

        buffer << input_stream.rdbuf();
        plain_data = buffer.str(); //Gets string for stringstream
        input_stream.close();

        output_stream.open(file_path, std::ios::binary | std::ios::trunc);
        if (!output_stream) {LOG("Failed to open save file for encryption", LFlags::FAILED);}

        std::string encrypted_data = encrypter->Encrypt(plain_data);
        output_stream.write(encrypted_data.data(), encrypted_data.size()); //.write for binary data
        output_stream.close();
        LOG("Encrypted save file", LFlags::SUCCESS);
    }

    std::string SDManager::DecryptSaveFile(Encrypter* encrypter) const
    {
        std::ifstream input_stream;

        std::string encrypted_data;
        std::stringstream buffer;

        input_stream.open(file_path, std::ios::binary);
        if (!input_stream) {LOG("Failed to open save file for decryption", LFlags::FAILED);}
        else 
        {
            buffer << input_stream.rdbuf();
            encrypted_data = buffer.str();
            return encrypter->Decrypt(encrypted_data);
        }
        return "";
    }

    SDManager::types SDManager::LoadData(std::string decrypted_data, std::string data_type, std::string data_name) const
    {    
        std::istringstream data_stream(decrypted_data); //Get stream from the decrypted data

        std::string line;
        while(std::getline(data_stream, line)) //Go through each line the stream
        {
            std::string name;
            std::string type;

            std::istringstream iss(line); //Parse the line into words
            iss >> name >> type; //Output fist word to name, second to type

            //If correct variable 
            if(name == data_name && type == data_type)
            {
                std::string value;
                iss >> value;

                // Create types object for returning any type
                auto _types = types();
                if (data_type == "double")
                {
                    _types = std::stod(value);
                }
                else if (data_type == "int")
                {
                    _types = std::stoi(value);
                }
                else if (data_type == "float")
                {
                   _types = std::stof(value);
                }
                else if (data_type == "bool")
                {
                    _types = std::stoi(value);
                }
                else if (data_type == "string")
                {
                    _types = helper::strReplace(value, '~', ' ');
                }
                std::string message = std::format("Successfully loaded {} from: {}", data_name, file_path);
                LOG(message, LFlags::SUCCESS);
                return _types;
            }
        }

        auto message = std::format("Couldn't find Data with the name: {} of type : {}", data_name, data_type);
        LOG(message, LFlags::ERROR);
        return types(); //Return empty variant
    }

    SDManager::SDManager() {};
}
