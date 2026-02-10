#pragma once

#include <cmath>
#include <algorithm>

#include "Vector2.hpp"

#include "Random.hpp"

namespace cmate::core::mathf
{
    class Vector2; // Forward Decleration = Compiler knows Vector2 exists, not what it contains

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

    Vector2 lerp(Vector2 from, Vector2 to, double t);

    //Define Inline Vector based functions 
    Vector2 sin(Vector2 input);
    Vector2 fract(Vector2 input);
}