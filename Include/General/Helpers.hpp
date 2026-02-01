#pragma once
#include <string>


namespace utils::helper
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

    //Macro for getting the variable name, may be relocated
    #define GET_VARIABLE_NAME(Variable) (#Variable)
}