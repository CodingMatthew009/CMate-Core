#pragma once

#include "DataEncrypter.hpp"
#include "General/Enums.hpp"
#include "General/Helpers.hpp"
#include "MLogger.hpp"


#include <type_traits>
#include <fstream>
#include <sstream> 
#include <cstdlib>
#include <variant>
#include <string>


namespace cmate::core
{
    class SDManager
    {
        public:

            //Variant: All members same memory adress, usefull for returning different types from same function
            // Pointer friendlier than union
            using types = std::variant<
                int,
                float,
                double,
                bool,
                std::string
            >;

            static SDManager& Instance();

            SDManager(const SDManager&) = delete;
            SDManager &operator=(const SDManager&) = delete;

            void SetSaveFile(std::string path);
            void SetSaveFile(const char* path);

            void ClearSaveFile() const;

            void EncryptSaveFile(Encrypter* encrypter) const;

            std::string DecryptSaveFile(Encrypter* encrypter) const;

            //Returns union with different types
            types LoadData(std::string decrypted_data, std::string data_type, std::string data_name) const;

            //Operator overloading using header implemented template
            //Saving data for different types (int, float, double, bool, string) 
            //External Function for Classes planed
            template<typename T> void SaveData(T t, std::string name, bool nonl = false) const
            {
                std::ofstream output_stream;

                output_stream.open(file_path, std::ios::app);
                if (!output_stream)
                {
                    LOG("Failed to open SaveFile", LFlags::FAILED);
                } 
                else 
                {
                    T value = t;
                    
                    //Check if type is string
                    if constexpr(std::is_same_v<T, std::string>)
                    {
                        //Replace all spaces with special character for correct word parsing
                        value = helper::strReplace(t, ' ', '~');
                    }

                    output_stream << name;
                    output_stream << " ";
                    output_stream << helper::VarTypeToString(t);
                    output_stream << " ";
                    output_stream << value;
                    if (!nonl) {output_stream << "\n";}
                    output_stream.close();
                }
            }

            // Variadic template for unset amount of paramaters
            template<typename... member> void SaveDataBlock(const char* instance_name, member&... variables)
            {
                std::ofstream output_stream;

                output_stream.open(file_path, std::ios::app);
                if (!output_stream)
                {
                    LOG("Failed to open SaveFile", LFlags::FAILED);
                } 
                else 
                {
                    output_stream << instance_name;
                    output_stream << "   ";

                    (SaveData(variables, "class_member", true), ...); // Variadic Template black magic

                    output_stream << "\n";
                    output_stream.close();
                } 
            }

        private:
            SDManager();
            std::string file_path;
    };
}