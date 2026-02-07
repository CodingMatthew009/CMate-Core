#pragma once

#include "INoise.hpp"
#include "../General.hpp"
#include "../Vector2.hpp"

#include <cmath>

using namespace utils::mathf;


namespace utils::Noise
{
    class WhiteNoise : public utils::Interfaces::INoise
    {
        public:
            WhiteNoise(int seed, Vector2 size)
            {
                for (int c = 0; c <= size.x; c++)
                {
                    std::vector<double> collumn;

                    for (int p = 0; p <= size.y; p++)
                    {
                        collumn.push_back(
                            fract(
                                std::sin(
                                    Vector2::dot(Vector2(c, p),
                                    Vector2(
                                        Random::dRangeS(0, 1000000, seed + c * 35281243 + p * 97246126), 
                                        Random::dRangeS(0, 1000000, seed + c * 28754621 + p * 21634512))) 
                                        * seed)));
                    }

                    value_map.push_back(collumn);
                }
            }
    };
}