#pragma once

#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <variant>
#include <type_traits>


#include "General/Enums.hpp"
#include "General/Helpers.hpp"
#include "MLogger.hpp"


namespace utils
{
    class SDManager
    {
        public:

            //Union: All members same memory adress, usefull for returning different types from same function
            using types = std::variant<
                int,
                float,
                double,
                bool,
                std::string>;

            static SDManager& Instance();

            SDManager(const SDManager&) = delete;
            SDManager &operator=(const SDManager&) = delete;

            void SetSaveFile(std::string path);
            void SetSaveFile(const char* path);

            //Returns union with different types
            types LoadData(std::string data_type, std::string data_name);

            //Operator overloading using header implemented template
            //Saving data for different types (int, float, double, bool, string) 
            //External Function for Classes planed
            template<typename T> void SaveData(T t, std::string name)
            {
                std::ofstream data_stream;
                data_stream.open(file_path, std::ios::app);

                if (!data_stream)
                {
                    LOG("Failed to open SaveFile", LFlags::ERROR);
                } 
                else 
                {
                    T value;
                    if constexpr(std::is_same_v<T, std::string>)
                    {
                        value = helper::strReplace(t, ' ', '~');
                    }
                    else 
                    {
                        value = t;
                    }

                    data_stream << name;
                    data_stream << " ";
                    data_stream << VarTypeToString(t);
                    data_stream << " ";
                    data_stream << value;
                    data_stream << "\n";
                    data_stream.close();
                }
            }

            //Helper Function to convert data type to a string of it, probably will be relocated
            template<typename T> static std::string VarTypeToString(T t)
            {
                if constexpr (std::is_same_v<T, int>)
                {
                    return "int";
                }
                if constexpr (std::is_same_v<T, double>)
                {
                    return "double";
                }
                if constexpr (std::is_same_v<T, float>)
                {
                    return "float";
                }
                if constexpr (std::is_same_v<T, bool>)
                {
                    return "bool";
                }
                if constexpr (std::is_same_v<T, std::string>)
                {
                    return "string";
                }
            }

        private:
            SDManager();
            std::string file_path;
    };

    #define SET_SAVE_FILE(path) \
        SDManager::Instance().SetSaveFile(path);

    //Macro for getting the variable name, may be relocated
    #define GET_VARIABLE_NAME(Variable) (#Variable)
}