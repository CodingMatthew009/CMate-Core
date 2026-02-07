#pragma once

#include "../../Imager.hpp"

#include <vector>

namespace utils
{
    class Imager; //Forward decleration of Imager

    namespace Interfaces {
        class INoise
        {
            public:

                int GetSeed() const
                {
                    return seed;
                }

                double GetValue(int pos_x, int pos_y)
                {
                    return value_map[pos_x][pos_y];
                }

                void SaveAsImage(std::string path)
                {
                    Imager::ValuesToBitmap(value_map, path);
                }

                void SaveAsImage(const char* path)
                {
                    Imager::ValuesToBitmap(value_map, path);
                }

            protected:
                int seed;

                std::vector<std::vector<double>> value_map;

        };
    }  
}