#pragma once

#include "Vector3.hpp"
#include "General.hpp"

namespace cmate::core::mathf
{
    class Vector3;

    class Vector2
    {
        public:
            double x;
            double y;

            Vector2(double x, double y);

            Vector2(const Vector2& other);

            explicit Vector2(const Vector3& other);
            

            //Methods
            Vector2 normalize();

            double magnitude();

            double sqrMagnitude();

            void set(double newx, double newy);

            void set(Vector2& other);

            // Static Functions
            static double Angle(Vector2 first, Vector2 second);

            static double dot(Vector2 first, Vector2 second);

            static double Distance(Vector2 first, Vector2 second);

            static Vector2 SmoothStep(Vector2 from, Vector2 second, double t);

            // Operator Overloads
            Vector2 operator- (Vector2 other) 
            {
                return Vector2(this->x - other.x, this->y - other.y);
            }

            Vector2 operator- (double value)
            {
                return Vector2(this->x - value, this->y - value);
            }

            Vector2 operator+ (Vector2 other) 
            {
                return Vector2(this->x + other.x, this->y + other.y);
            }

            Vector2 operator+ (double value)
            {
                return Vector2(this->x + value, this->y + value);
            }

            Vector2 operator* (double factor) 
            {
                return Vector2(this->x * factor, this->y * factor);
            }

            Vector2 operator/ (double factor) 
            {
                return Vector2(this->x / factor, this->y / factor);
            }

            #define V2_UP Vector2(0, 1)
            #define V2_DOWN Vector2(0, -1)
            #define V2_LEFT Vector2(-1, 0)
            #define V2_RIGHT Vector2(1, 0)

            #define V2_ONE Vector2(1, 1)
            #define V2_ZERO Vector2(0, 0)
    }; 
}

#include "General.inl"  // Implement inline functions after Vector2 and 3 Exist, (.inl => .hpp)
