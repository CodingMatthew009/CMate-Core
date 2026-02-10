#include "../../Include/Math/Vector3.hpp"
#include <cmath>

namespace cmate::core::mathf
{
    Vector3::Vector3(double other_x, double other_y, double other_z)
    {
        x = other_x; y = other_y; z = other_z;
    }

    Vector3::Vector3(const Vector3& other)
    {
        x = other.x; y = other.y; z = other.z;
    }

    Vector3::Vector3(const Vector2& other)
    {
        x = other.x; y = other.y; z = 0;
    }

    //Methods
    Vector3 Vector3::normalize()
    {
        return Vector3(x / magnitude(), y / magnitude(), z / magnitude());
    }

    double Vector3::magnitude()
    {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
    }

    double Vector3::sqrMagnitude()
    {
        return std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
    }

    void Vector3::set(double newx, double newy, double newz)
    {
        x = newx; y = newy; z = newz;
    }

    void Vector3::set(Vector3& other)
    {
        x = other.x; y = other.y; z = other.z;
    }

    double Vector3::Angle(Vector3 first, Vector3 second)
    {
        double radians = std::acos(dot(first, second) / (first.magnitude() * second.magnitude()));
        double degrees = radians * (180/M_PI);
        return degrees;
    }

    double Vector3::dot(Vector3 first, Vector3 second)
    {
        return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
    }

    double Vector3::Distance(Vector3 first, Vector3 second)
    {
        return (first - second).magnitude();
    }
}