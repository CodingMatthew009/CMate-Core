#pragma once

#include <random>

namespace utils::mathf
{
    class Random
    {
    public:
        static int iRange(int min, int max);

        static double dRange(double min, double max);

        static int iRangeS(int min, int max, int seed);

        static double dRangeS(double min, double max, int seed);
    };
}