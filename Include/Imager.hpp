#pragma once

#include "MLogger.hpp"
#include "Color.hpp"

#include <fstream>
#include <vector>
#include <string>

namespace cmate::core
{
    
    //Constant data for bmp files
    const int data_offset = 54;
    const int info_header_size = 40;
    const int planes = 1;
    const int color_accuracy = 24; //BGR = 24 bits

    class Imager
    {
    public:
        static void ValuesToBitmap(std::vector<double> value_array, int width, std::string image_path);

        static void ValuesToBitmap(std::vector<double> value_array, int width, const char* image_path);
    };
}