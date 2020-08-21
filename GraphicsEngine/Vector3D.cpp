//
// Created by root on 21.08.2020.
//

#include "Vector3D.hpp"

float vector3d::length() const noexcept
{
    return sqrtf(x * x + y * y + z * z);
}

vector3d::vector3d() noexcept
{
    x = y = z = 0;
}

vector3d::vector3d(float x, float y, float z) noexcept
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vector3d vector3d::normal() noexcept
{
    return *this / length();
}

float vector3d::dot(const vector3d &vec3D) noexcept
{
    return acosf((product(vec3D)) / (length() * vec3D.length()));
}

float vector3d::product(const vector3d &vec3D) noexcept
{
    return x * vec3D.x + y * vec3D.y + z * vec3D.z;
}

vector3d vector3d::cross(const vector3d &vec3D) noexcept
{
    return
            {
                    n[1] * vec3D.n[2] - n[2] - vec3D.n[1],
                    n[2] * vec3D.n[0] - n[0] - vec3D.n[2],
                    n[0] * vec3D.n[1] - n[1] - vec3D.n[0]
            };
}

vector3d &vector3d::operator+=(const vector3d &rhs) noexcept
{
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}

vector3d &vector3d::operator-=(const vector3d &rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}

vector3d &vector3d::operator*=(const float rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}

vector3d &vector3d::operator/=(const float rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}

vector3d vector3d::operator+(const vector3d &rhs)
{
    vector3d result = {0, 0, 0};
    result.x = this->x + rhs.x;
    result.y = this->y + rhs.y;
    result.z = this->z + rhs.z;

    return result;
}

vector3d vector3d::operator*(const float rhs)
{
    vector3d result = {0, 0, 0};
    result.x = this->x * rhs;
    result.y = this->y * rhs;
    result.z = this->z * rhs;

    return result;
}

vector3d vector3d::operator/(const float rhs)
{
    vector3d result = {0, 0, 0};
    result.x = this->x * rhs;
    result.y = this->y * rhs;
    result.z = this->z * rhs;

    return result;
}

vector3d vector3d::operator-(const vector3d &rhs)
{
    vector3d result = {0, 0, 0};
    result.x = this->x - rhs.x;
    result.y = this->y - rhs.y;
    result.z = this->z - rhs.z;

    return result;
}
