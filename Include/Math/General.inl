#pragma once

namespace cmate::core::mathf
{
    inline Vector2 sin(Vector2 input)
    {
        Vector2 result = Vector2(
            std::sin(input.x),
            std::sin(input.y)
        );

        return result;
    }

    inline Vector2 fract(Vector2 input)
    {
        Vector2 result = Vector2(
            input.x - std::floor(input.x),
            input.y - std::floor(input.y)
        );
        
        return result;
    }

    inline Vector2 lerp(Vector2 from, Vector2 to, double t)
    {
        return from * t + to * (1 - t);
    }

}