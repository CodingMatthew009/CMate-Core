#pragma once
#include <vector>

namespace interfaces
{
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

        protected:
            int seed;

            std::vector<std::vector<double>> value_map;

    };
}