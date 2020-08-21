//
// Created by root on 21.08.2020.
//
#include <cmath>


#ifndef GRAPHICSENGINE_VECTOR3D_HPP
#define GRAPHICSENGINE_VECTOR3D_HPP

struct vector3d
{
    union
    {
        struct
        {
            float x, y, z;
        };
        struct
        {
            float pitch, yaw, roll;
        };
        float n[3] = {0.0f, 0.0f, 0.0f};
    };

    vector3d() noexcept;
    vector3d(float x, float y, float z) noexcept;

    inline float length() const noexcept;
    inline float dot(const vector3d &vec3D) noexcept;
    inline float product(const vector3d& vec3D) noexcept;
    vector3d normal() noexcept;
    vector3d cross(const vector3d& vec3D) noexcept;
    vector3d operator+(const vector3d& rhs);
    vector3d operator-(const vector3d& rhs);
    vector3d operator*(const float rhs);
    vector3d operator/(const float rhs);
    vector3d& operator+= (const vector3d& rhs) noexcept;
    vector3d& operator-= (const vector3d& rhs);
    vector3d& operator*= (const float rhs);
    vector3d& operator/= (const float rhs);
};

#endif //GRAPHICSENGINE_VECTOR3D_HPP
