#pragma once

#include "INoise.hpp"
#include "../General.hpp"
#include "../Vector2.hpp"


using namespace cmate::core::mathf;


namespace cmate::core::Noise
{
    class WhiteNoise : public cmate::core::Interfaces::INoise
    {
        public:
            WhiteNoise(int seed, unsigned int pixel_size, bool log_gen_time = false)
            {
                for (int c = 0; c < pixel_size; c++)
                {
                    std::vector<double> collumn;

                    for (int p = 0; p < pixel_size; p++)
                    {
                        collumn.push_back(hash(Vector2(c, p), seed));
                    }

                    value_map.push_back(collumn);
                }

                if (log_gen_time)
                {
                    LOG("Generation of White Noise Completed", LFlags::INFO);
                }
            }
    };
}