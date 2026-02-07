#pragma once

#include <cstdint>
#include <vector>

namespace utils
{
    struct Color
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;

        Color() {};
        Color(uint8_t red, uint8_t green, uint8_t blue)
        {   
            R = red; G = green; B = blue;
        }
    };

    inline Color ValueToColor(double value)
    {
        Color color(
            value * 255,
            value * 255,
            value * 255
        );
        return color;
    }

    inline std::vector<std::vector<Color>> ValueMapToPixelMap(std::vector<std::vector<double>> values)
    {
        std::vector<std::vector<Color>> collumns;
        for (int c = 0; c < values.size(); c++)
        {
            std::vector<Color> pixels;
            for (int i = 0; i < values[c].size(); i++)
            {
                pixels.push_back(ValueToColor(values[c][i]));
            }

            collumns.push_back(pixels);
        }
        return collumns;
    } 
}