#include "../../Include/Math/Random.hpp"
#include <random>

namespace utils::mathf 
{
    int Random::iRange(int min, int max)
    {
        std::random_device rd;
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(rd);
    }

    double Random::dRange(double min, double max)
    {
        std::random_device rd;
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(rd);
    }

    int Random::iRangeS(int min, int max, int seed)
    {
        std::mt19937 rd(seed);
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(rd);
    }

    double Random::dRangeS(double min, double max, int seed)
    {
        std::mt19937 rd(seed);
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(rd);
    }
}