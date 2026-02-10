#pragma once

#include "MLogger.hpp"
#include "Color.hpp"

#include <fstream>
#include <vector>
#include <string>

namespace cmate::core
{
    class Imager
    {
    public:
        static void ValuesToBitmap(std::vector<std::vector<double>> value_array, std::string image_path);

        static void ValuesToBitmap(std::vector<std::vector<double>> value_array, const char* image_path);
    };
}