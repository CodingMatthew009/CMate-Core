#pragma once

#include "INoise.hpp"
#include "../General.hpp"
#include "../Vector2.hpp"


using namespace cmate::core::mathf;


namespace cmate::core::Noise
{
    class VoronoiNoise : public cmate::core::Interfaces::INoise
    {
        public:
            VoronoiNoise(int seed, unsigned int pixel_size, unsigned int noise_size, bool log_gen_time = false)
            {
                for (int c = 0; c < pixel_size; c++)
                {
                    std::vector<double> collumn;
                    for (int p = 0; p < pixel_size; p++)
                    {
                        //Meth, dont know what it is, it just works :)

                        double noise_x = (c / ((double)pixel_size - 1)) * (double)noise_size;
                        double noise_y = (p / ((double)pixel_size - 1)) * (double)noise_size;
                        Vector2 floored_pos = Vector2(std::floor(noise_x), std::floor(noise_y));
                        Vector2 fract_coords = Vector2(fract(noise_x), fract(noise_y));

                        double res = 0.0;

                        for (int j = -1; j <= 1; j++)
                        {
                            for (int i = -1; i <= 1; i++)
                            {
                                Vector2 b = Vector2(double(i), double(j));
                                Vector2 r = b - fract_coords + hash(floored_pos + b, seed);
                                res += 0.1/pow(Vector2::dot(r, r), 8.0);
                            }
                        }
                        
                        collumn.push_back(pow(1./res, 0.0625));       
                    }

                    value_map.push_back(collumn);
                }

                if (log_gen_time)
                {
                    LOG("Generation of Voronoi Noise Completed", LFlags::INFO);
                }
            }
    };
}