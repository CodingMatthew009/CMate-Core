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

    inline std::vector<Color> ValuesToColors(std::vector<double> values)
    {
        std::vector<Color> colors;
        for (int i = 0; i <= values.size(); i++)
        {
            colors.push_back(ValueToColor(values[i]));
        }
        return colors;
    } 
}