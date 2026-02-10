#pragma once

#include "INoise.hpp"
#include "../General.hpp"
#include "../Vector2.hpp"


using namespace cmate::core::mathf;


namespace cmate::core::Noise
{
    class PerlinNoise : public cmate::core::Interfaces::INoise
    {
        public:
            PerlinNoise(int seed, Vector2 size, Vector2 noise_size)
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

                        double value = 0.5 + (0.5 * std::lerp( std::lerp( Vector2::dot( hash2D(floored_pos + V2_ZERO, seed), fract_coords - V2_ZERO ),
                                        Vector2::dot( hash2D(floored_pos + V2_RIGHT, seed), fract_coords - V2_RIGHT ), interpolated_vector.x),
                                    std::lerp( Vector2::dot( hash2D(floored_pos + V2_UP, seed) , fract_coords - V2_UP) ,
                                        Vector2::dot( hash2D(floored_pos + V2_ONE, seed) , fract_coords - V2_ONE), interpolated_vector.x), interpolated_vector.y));
                    

                        /* return 0.5 + (0.5 * mix( mix( dot( hash2d(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                                    dot( hash2d(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                                mix( dot( hash2d(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                                    dot( hash2d(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y));*/

                        collumn.push_back(value);       
                    }

                    value_map.push_back(collumn);
                }
            }
    };
}