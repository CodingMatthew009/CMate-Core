#pragma once

#include "Vector2.hpp"
namespace cmate::core::mathf
{
    class Vector2;

    class Vector3
    {
        public:
            double x;
            double y;
            double z;

            Vector3(double x, double y, double z);

            Vector3(const Vector3& other);

            explicit Vector3(const Vector2& other);
            

            //Methods
            Vector3 normalize();

            double magnitude();

            double sqrMagnitude();

            void set(double newx, double newy, double newz);

            void set(Vector3& other);

            static double Angle(Vector3 first, Vector3 second);

            static double dot(Vector3 first, Vector3 second);

            static double Distance(Vector3 first, Vector3 second);

            Vector3 operator- (Vector3 other) 
            {
                return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
            }

            Vector3 operator+ (Vector3 other) 
            {
                return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
            }

            Vector3 operator* (double factor) 
            {
                return Vector3(this->x * factor, this->y * factor, this->z * factor);
            }

            Vector3 operator/ (double factor) 
            {
                return Vector3(this->x / factor, this->y / factor, this->z / factor);
            }

            #define V3_UP Vector3(0, 1, 0)
            #define V3_DOWN Vector3(0, -1, 0)
            #define V3_LEFT Vector3(-1, 0, 0)
            #define V3_RIGHT Vector3(1, 0, 0)

            #define V3_FORWARD Vector3(0, 0, 1)
            #define V3_BACKWARD Vector3(0, 0, -1)

            #define V3_ONE Vector3(1, 1, 1)
            #define V3_ZERO Vector3(0, 0, 0)
    }; 
}