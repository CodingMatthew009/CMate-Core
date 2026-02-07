#include "../../Include/Math/Vector2.hpp"
#include <cmath>
#include <algorithm>

namespace utils::mathf
{
    

    Vector2::Vector2(double other_x, double other_y)
    {
        x = other_x; y = other_y;
    }

    Vector2::Vector2(const Vector2& other)
    {
        x = other.x; y = other.y;
    }

    Vector2::Vector2(const Vector3& other)
    {
        x = other.x; y = other.y;
    }

    //Methods
    Vector2 Vector2::normalize()
    {
        return Vector2(x / magnitude(), y / magnitude());
    }

    double Vector2::magnitude()
    {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    double Vector2::sqrMagnitude()
    {
        return std::pow(x, 2) + std::pow(y, 2);
    }

    void Vector2::set(double newx, double newy)
    {
        x = newx; y = newy;
    }

    void Vector2::set(Vector2& other)
    {
        x = other.x; y = other.y;
    }

    // Static functions
    double Vector2::Angle(Vector2 first, Vector2 second)
    {
        double radians = std::acos(dot(first, second) / (first.magnitude() * second.magnitude()));
        double degrees = radians * (180/M_PI);
        return degrees;
    }

    double Vector2::dot(Vector2 first, Vector2 second)
    {
        return (first.x * second.x) + (first.y * second.y);
    }

    double Vector2::Distance(Vector2 first, Vector2 second)
    {
        return (first - second).magnitude();
    }

    Vector2 Vector2::SmoothStep(Vector2 from, Vector2 to, double t)
    {
        Vector2 result(
            mathf::SmoothStep(from.x, to.x, t),
            mathf::SmoothStep(from.x, to.x, t)
        );

        return result;
    }
}