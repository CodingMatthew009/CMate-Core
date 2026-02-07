#pragma once

#include "INoise.hpp"
#include "../General.hpp"
#include "../Vector2.hpp"
#include "../../Imager.hpp"

#include <cmath>

using namespace utils::mathf;


namespace utils::noise
{
    class WhiteNoise : interfaces::INoise
    {
        public:
            WhiteNoise(int seed, Vector2 size)
            {
                for (int c = 0; c <= size.x; c++)
                {
                    std::vector<double> collon;

                    for (int p = 0; p <= size.y; p++)
                    {
                        collon.push_back(fract(std::sin(Vector2::dot(Vector2(c, p), Vector2(12.9898, 78.233)) * seed)));
                    }

                    value_map.push_back(collon);
                }

                // Pack raw values to image
                Imager::ValuesToBitmap(value_map, "/home/mate/Projects/Mate-Utils/white_noise.bmp");
            }
    };
}