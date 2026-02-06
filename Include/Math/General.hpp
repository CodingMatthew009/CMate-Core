#pragma once

#include <cmath>

namespace utils::mathf
{
    //Missing functions from cmath 
    inline double fract(double x)
    {
        return x - std::floor(x);
    }
}