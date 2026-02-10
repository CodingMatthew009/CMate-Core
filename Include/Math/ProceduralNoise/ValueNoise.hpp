#pragma once

#include "INoise.hpp"
#include "../General.hpp"
#include "../Vector2.hpp"


using namespace cmate::core::mathf;


namespace cmate::core::Noise
{
    class ValueNoise : public cmate::core::Interfaces::INoise
    {
        public:
            ValueNoise(int seed, Vector2 size, Vector2 noise_size)
            {
                for (int c = 0; c < size.x; c++)
                {
                    std::vector<double> collumn;

                    for (int p = 0; p < size.y; p++)
                    {
                        double noise_x = (c / (size.x - 1)) * noise_size.x;
                        double noise_y = (p / (size.y - 1)) * noise_size.y;

                        Vector2 floored_pos = Vector2(std::floor(noise_x), std::floor(noise_y));

                        Vector2 fract_coords = Vector2(fract(noise_x), fract(noise_y));

                        Vector2 interpolated_vector = Vector2(SmoothStep(0, 1, fract_coords.x), SmoothStep(0, 1, fract_coords.y));

                        double a = hash(floored_pos, seed);
                        double b = hash(floored_pos + V2_RIGHT, seed);
                        double c_ = hash(floored_pos + V2_UP, seed);
                        double d = hash(floored_pos + V2_ONE, seed);

                        double value = std::lerp(std::lerp(a, b, interpolated_vector.x), std::lerp(c_, d, interpolated_vector.x), interpolated_vector.y);

                        collumn.push_back(value);       
                    }

                    value_map.push_back(collumn);
                }
            }
    };
}