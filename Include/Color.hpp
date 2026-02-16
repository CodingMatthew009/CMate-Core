#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

#include "Math/General.hpp"

namespace cmate::core
{
    struct Color
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;

        Color() {};
        Color(uint8_t red, uint8_t green, uint8_t blue)
        {   
            red = std::clamp((int)red, 0, 255);
            green = std::clamp((int)green, 0, 255);
            blue = std::clamp((int)blue, 0, 255);

            R = red; G = green; B = blue;
        }

        inline Color operator+(Color& other)
        {
            Color result(
                R + other.R,
                G + other.G,
                B + other.G
            );

            return result;
        }

        inline Color operator-(Color& other)
        {
            Color result(
                R - other.R,
                G - other.G,
                B - other.G
            );

            return result;
        }

        inline Color operator*(double factor)
        {
            Color result(
                R * factor,
                G * factor,
                B * factor
            );

            return result;
        }

        inline Color SmoothStep(Color& from, Color& to, double t)
        {
            Color result(
                mathf::SmoothStep(from.R, to.R, t),
                mathf::SmoothStep(from.G, to.G, t),
                mathf::SmoothStep(from.B, to.B, t)
            );

            return result;
        }
    };

    inline bool operator< (Color& color1, Color& color2)
    {
        if (color1.R < color2.R &&
            color1.G < color2.G &&
            color1.B < color2.B)
        {
            return true;
        }
        return false;
    }

    inline bool operator> (Color& color1, Color& color2)
    {
        if (color1.R > color2.R &&
            color1.G > color2.G &&
            color1.B > color2.B)
        {
            return true;
        }
        return false;
    }

    inline bool operator<= (Color& color1, Color& color2)
    {
        if (color1.R <= color2.R &&
            color1.G <= color2.G &&
            color1.B <= color2.B)
        {
            return true;
        }
        return false;
    }

    inline bool operator>= (Color& color1, Color& color2)
    {
        if (color1.R >= color2.R &&
            color1.G >= color2.G &&
            color1.B >= color2.B)
        {
            return true;
        }
        return false;
    }

    inline bool operator== (Color& color1, Color& color2)
    {
        if (color1.R == color2.R &&
            color1.G == color2.G &&
            color1.B == color2.B)
        {
            return true;
        }
        return false;
    }    

    inline Color ValueToColor(double value)
    {
        Color color(
            value * 255,
            value * 255,
            value * 255
        );
        return color;
    }

    inline double ColorToValue(Color& color)
    {
        double value = (double)(color.R + color.G + color.B) / 3 / 255;
        return value;
    }
}