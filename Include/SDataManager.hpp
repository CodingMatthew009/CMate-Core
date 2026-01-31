#pragma once

#include <fstream>
#include <cstdlib>
#include <sstream>
#include <variant>
#include <type_traits>


#include "General/Enums.hpp"
#include "MLogger.hpp"


namespace utils
{
    class SDManager
    {
        public:
            union types {
                int _int;
                float _float;
                double _double;
                bool _bool;
            };

            static SDManager& Instance();

            SDManager(const SDManager&) = delete;
            SDManager &operator=(const SDManager&) = delete;

            void SetSaveFile(std::string path);
            void SetSaveFile(const char* path);

            types LoadData(std::string data_type, std::string data_name);

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
                    data_stream << name;
                    data_stream << " ";
                    data_stream << VarTypeToString(t);
                    data_stream << " ";
                    data_stream << t;
                    data_stream << "\n";
                    data_stream.close();
                }
            }

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
            }

        private:
            SDManager();
            std::string file_path;
    };

    #define GET_VARIABLE_NAME(Variable) (#Variable)
}