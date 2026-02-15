#pragma once

#include <cstdint>
#include <vector>

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
            R = red; G = green; B = blue;
        }

        inline Color operator+(Color other)
        {
            Color result(
                R + other.R,
                G + other.G,
                B + other.G
            );

            return result;
        }

        inline Color operator-(Color other)
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

        inline Color SmoothStep(Color from, Color to, double t)
        {
            Color result(
                mathf::SmoothStep(from.R, to.R, t),
                mathf::SmoothStep(from.G, to.G, t),
                mathf::SmoothStep(from.B, to.B, t)
            );

            return result;
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

    inline double ColorToValue(Color color)
    {
        double value = (double)(color.R + color.G + color.B) / 3 / 255;
        return value;
    }

    inline std::vector<Color> ValueMapToPixelMap(std::vector<double> values)
    {
        std::vector<Color> pixels;
        for (int c = 0; c < values.size(); c++)
        {
            pixels.push_back(ValueToColor(values[c]));
        }
        return pixels;
    } 

    inline std::vector<double> PixelMapToValueMap(std::vector<Color> pixels)
    {
        std::vector<double> values;
        for (int i = 0; i < pixels.size(); i++)
        {
            values.push_back(ColorToValue(pixels[i]));
        }
        return values;
    } 
}