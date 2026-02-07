#pragma once

#include <cmath>
#include <algorithm>

#include "Vector2.hpp"

#include "Random.hpp"

namespace utils::mathf
{
    class Vector2;

    //Missing functions from cmath 
    inline double fract(double x)
    {
        return x - std::floor(x);
    }

    inline double SmoothStep(double from, double to, double amount)
    {
        float t = std::clamp((amount - from) / (to - from), (double)0.0, (double)1.0);

        return t * t * (3.0 - 2.0 * t);
    }
}