#pragma once
#include <string>


namespace cmate::core::helper
{
    static inline std::string strReplace(std::string input, 
                                        char charToReplace, 
                                        char charToPlace)
    {
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == charToReplace)
            {
                input[i] = charToPlace;
            }
        }

        return input;
    }

    //Helper Function to convert data type to a string of it, probably will be relocated
    template<typename T> inline static std::string VarTypeToString(T t)
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

    //Macro for getting the variable name, may be relocated
    #define GET_VARIABLE_NAME(Variable) (#Variable)
}