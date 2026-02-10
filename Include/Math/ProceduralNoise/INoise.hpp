#pragma once

#include "../../Imager.hpp"
#include "../Vector2.hpp"
#include "../Random.hpp"

#include <vector>
#include <cmath>

namespace cmate::core
{
    class Imager; //Forward decleration of Imager

    namespace Interfaces {
        class INoise
        {
            public:

                int GetSeed() const
                {
                    return seed;
                }

                double GetValue(int pos_x, int pos_y)
                {
                    return value_map[pos_x][pos_y];
                }

                void SaveAsImage(std::string path)
                {
                    Imager::ValuesToBitmap(value_map, path);
                }

                void SaveAsImage(const char* path)
                {
                    Imager::ValuesToBitmap(value_map, path);
                }

            protected:
                int seed;

                std::vector<std::vector<double>> value_map;

        };
    }  

    namespace mathf {

        // Hashing function for White-Value Noise (Slow and CPU Unfriendly)
        inline double hash(Vector2 inputVec, int seed)
        {
           return fract(
                    std::sin(
                        Vector2::dot(inputVec, 
                            Vector2(Random::dRangeS(0, 1000000, seed + inputVec.x * 35281 + inputVec.y * 97246), 
                                    Random::dRangeS(0, 1000000, seed + inputVec.x * 28754 + inputVec.y * 21634)
                                ))* seed));
        }

        // Hashing function for Perlin Noise (No idea whats going on)
        inline Vector2 hash2D(Vector2 inputVec, int seed)
        {
            int x = int(inputVec.x);
            int y = int(inputVec.y);
        
            uint32_t h = seed;

            // Gives huge variation between each coordinate 
            h ^= x * 374761393u; // Bitwise XOR Operation same as h = h ^ x * ..
            h ^= y * 668265263u;

            h = (h ^ (h >> 13)) * 1274126177u;
            double angle = (h & 0xFFFF) / double(0xFFFF) * 2.0 * M_PI; // 0xFFFF = 00000000 00000000 11111111 11111111, so & keeps only 16 bits
            return Vector2(std::cos(angle), std::sin(angle));
        }
    }
}